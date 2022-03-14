/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/10 16:05:22 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_outdir(t_dir **out, t_dir **infile, int bis, char *cmd)
{
	int		i;
	int		compt;

	i = -1;
	if (bis == 2)
		return (put_outdir_upto_last_indir(out, infile, cmd));
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '>' && bool_not_in_quotes(&cmd[i]))
		{
			i++;
			compt++;
		}
		if (compt == 1)
			create_out_list(out, cmd, i, 1);
		else if (compt == 2)
			create_out_list(out, cmd, i, 2);
		else if (compt > 2)
			return (ft_error("syntax error near unexpected token `>'\n"));
	}
	if (!*out)
		return (1);
	return (0);
}

int	put_outdir_upto_last_indir(t_dir **out, t_dir **infile, char *cmd)
{
	int		i;
	t_dir	*ptr;
	int		compt;

	i = -1;
	ptr = go_to_last(infile);
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '>')
		{
			i++;
			compt++;
		}
		if (i <= ptr->pos)
		{
			if (compt == 1 && bool_not_in_quotes(&cmd[i]))
				create_out_list(out, cmd, i, 1);
			else if (compt == 2 && bool_not_in_quotes(&cmd[i]))
				create_out_list(out, cmd, i, 2);
			else if (compt > 2 && bool_not_in_quotes(&cmd[i]))
				return (ft_error("syntax error near unexpected token `>'\n"));
		}
		else
		{
			if (*out)
			{
				ptr = go_to_last(out);
				close(ptr->fd);
			}
			return (1);
		}
	}
	if (!*out)
		return (1);
	return (0);
}

void	create_out_list(t_dir **out, char *cmd, int i, int flag)
{
	t_dir	*ptr;

	if (!*out)
	{
		if (flag == 1)
			*out = create_out_maillon(cmd, i, 1);
		else
			*out = create_out_maillon(cmd, i, 2);
		if (!*out)
			return ;
	}
	else
	{
		ptr = go_to_last(out);
		close(ptr->fd);
		if (flag == 1)
			ptr->next = create_out_maillon(cmd, i, 1);
		else
			ptr->next = create_out_maillon(cmd, i, 2);
		if (!ptr->next)
			return ;
	}
}

t_dir	*create_out_maillon(char *cmd, int i, int flag)
{
	char	*lim;
	t_dir	*tmp;

	tmp = ft_calloc(sizeof(t_dir), 1);
	if (!tmp)
		return (NULL);
	tmp->fd = -1;
	tmp->next = NULL;
	lim = get_limiteur(&cmd[i]);
	if (!lim)
		return (tmp);
	if (flag == 1)
		tmp->fd = open(lim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		tmp->fd = open(lim, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (tmp->fd == -1)
		perror("open");
	free(lim);
	return (tmp);
}
