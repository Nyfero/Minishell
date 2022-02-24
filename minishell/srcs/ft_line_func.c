/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/02/24 10:53:09 by gsap             ###   ########.fr       */
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
			printf("1er maillon\n");
			if (!*line)
				return ;
		}
		else
		{
			ptr = *line;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = create_line();
			printf("maillon\n");
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
	printf("element\n");
	return (line);
}

/*
**	verifier que tous les mallocs sont bien detruits
*/

void	destroy_list_line(t_line** line)
{
	t_line	*ptr;
	t_line	*aux;

	ptr = *line;
	while (ptr != NULL)
	{
		aux = ptr;
		ptr = ptr->next;
		free(aux->cmd);
		free(aux);
		printf("free\n");
	}
	*line = NULL;
}
