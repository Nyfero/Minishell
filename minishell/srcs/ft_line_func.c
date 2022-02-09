/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/02/09 16:09:13 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list_line(t_line **line, int len)
{
	t_line	*ptr;
	int		i;

	if (len == 0)
		return ;
	i = -1;
	while (++i < len)
	{
		if (!*line)
		{
			*line = create_line();
			if (!*line)
				return ;
		}
		else
		{
			ptr = *line;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = create_line();
			if (!ptr->next)
				return ;
		}
	}
}

t_line	*create_line(void)
{
	t_line	*line;

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (NULL);
	line->infile = NULL;
	line->outfile = NULL;
	line->cmd = NULL;
	line->indir = 0;
	line->outdir = 0;
	line->env = NULL;
	line->next = NULL;
	return (line);
}

void deallocate(t_line** root)
{
	t_line	*curr;
	t_line	*aux;

	curr = *root;
	while (curr != NULL)
	{
		aux = curr;
		curr = curr->next;
		free(aux->cmd);
		free(aux);
	}
	*root = NULL;
}
