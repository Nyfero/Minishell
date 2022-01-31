/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/01/31 18:16:44 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_addlist(t_line **line, char *inpt)
{
	t_line	*ptr;

	if (!(line && inpt))
		exit(5);
	if (!*line)
	{
		*line = minishell_create_list(inpt);
		if (!*line)
			exit(6);
	}
	else
	{
		ptr = *line;
		while (ptr->next)
		ptr = ptr->next;
		ptr->next = minishell_create_list(inpt);
		if (!ptr->next)
			exit(7);
	}
}

t_line	*minishell_create_list(char *inpt)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line = set_list_null(line);
	line->cmd = ft_strdup(inpt);
	return (line);
}

t_line	*set_list_null(t_line *line)
{
	line->infile = NULL;
	line->outfile = NULL;
	line->cmd = NULL;
	line->indir = 0;
	line->outdir = 0;
	line->env = NULL;
	return (line);
}


void	minishell_del_list(t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	while (line)
	{
		tmp = line->next;
		free(line->cmd);
		free(line);
		line = NULL;
		line = tmp;
	}
}
