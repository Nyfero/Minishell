/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/03 15:10:13 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_outdir(t_in **out, char *cmd)
{
	int		i;
	int		compt;
	t_in	*ptr;

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
			create_out_maillon(cmd, i, 1);
		else if (compt == 2)
			create_out_maillon(cmd, i, 2);
		else if (compt > 2)
		{
			ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
			return ;
		}
	}
}

t_in	*create_here_maillon(char *cmd, int i)
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
	lim = grep_indir(&cmd[i - 2]);
	printf("lim: %s\n", lim);
	tmp->fd = write_here_doc_on_fd(lim);
	free(lim);
	tmp->next = NULL;
	return (tmp);
}
