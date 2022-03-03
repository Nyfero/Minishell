/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/03 15:38:14 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_outdir(t_in **out, char *cmd)
{
	int		i;
	int		compt;

	i = -1;
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '>')
		{
			i++;
			compt++;
		}
		if (compt == 1)
			create_out_list(out, cmd, i, 1);
		else if (compt == 2)
			create_out_list(out, cmd, i, 2);
		else if (compt > 2)
		{
			ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
			return ;
		}
	}
}

void	create_out_list(t_in **out, char *cmd, int i, int flag)
{
	t_in	*ptr;

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
		if (flag == 1)
			ptr->next = create_out_maillon(cmd, i, 1);
		else
			ptr->next = create_out_maillon(cmd, i, 2);
		if (!ptr->next)
			return ;
	}
}

t_in	*create_out_maillon(char *cmd, int i, int flag)
{
	char 	*lim;
	t_in	*tmp;

	tmp = ft_calloc(sizeof(t_in), 1);
	if (!tmp)
	{
		ft_putstr_fd("Error malloc t_in\n", 2);
		return (NULL);
	}
	tmp->pos = i - 2;
	tmp->next = NULL;
	lim = get_limiteur(&cmd[i]);
	if (flag == 1)
		tmp->fd = open(lim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		tmp->fd = open(lim, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (tmp->fd == -1)
		perror("open");
	free(lim);
	return (tmp);
}
