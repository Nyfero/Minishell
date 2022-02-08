/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/02/08 15:05:16 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Créer line ou rajoute un maillon a line
*/

void	minishell_addlist(t_line **line, char *inpt)
{
	t_line	*ptr;

	if (!(line && inpt))
		return ;
	if (!*line)
	{
		*line = minishell_create_list(inpt);
		if (!*line)
			return ;
	}
	else
	{
		ptr = *line;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = minishell_create_list(inpt);
		if (!ptr->next)
			return ;
	}
	return ;
}

/*
**	Initialisation du maillon
*/

t_line	*minishell_create_list(char *inpt)
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
	line->cmd = ft_strdup(inpt);
	if (!line->cmd)
		return (0);
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

/*void	minishell_del_list(t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	while (line)
	{
		tmp = NULL;
		if (line->next)
			tmp = line->next;
		line->next = NULL;
		if (line->cmd)
			free(line->cmd);
		free(line);
		line = tmp;
	}
}*/
