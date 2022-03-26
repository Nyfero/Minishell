/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/26 16:45:16 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_outdir(char *cmd)
{
	int		i;
	int		out;
	int		compt;

	i = -1;
	out = 1;
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '>' && bool_not_in_quotes(&cmd[i]))
		{
			i++;
			compt++;
		}
		if (compt == 1)
			out = create_out(out, cmd, i, 1);
		else if (compt == 2)
			out = create_out(out, cmd, i, 2);
		else if (compt > 2)
			return (print_error_syntax(1));
		if (out == -2)
			return (out);
	}
	return (out);
}

int	put_outdir_upto_last_indir(int out, t_dir *infile, char *cmd)
{
	int		i;
	int		compt;

	i = 0;
	while (cmd[i])
	{
		compt = 0;
		while (cmd[i++] == '>' && bool_not_in_quotes(&cmd[i]))
			compt++;
		if (compt > 0)
		{
			if (i <= infile->pos)
			{
				if (compt <= 2)
					out = choice_outdir(compt, out, cmd, i - 1);
				if (compt > 2)
					return (print_error_syntax(1));
			}
			else
				return (out);
			if (out == -2)
				return (out);
		}
	}
	return (out);
}

int	create_out(int out, char *cmd, int i, int flag)
{
	char	*lim;

	if (out != 1)
		close(out);
	lim = get_limiteur(&cmd[i]);
	if (!lim)
		return (-2);
	if (flag == 1)
		out = open(lim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		out = open(lim, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out == -1)
		perror("open");
	free(lim);
	return (out);
}

void	destroy_dir(t_dir **dir)
{
	t_dir	*ptr;
	t_dir	*aux;

	ptr = *dir;
	while (ptr)
	{
		aux = ptr;
		ptr = ptr->next;
		aux->next = NULL;
		free(aux);
	}
	*dir = NULL;
}
