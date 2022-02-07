/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/02/07 17:37:56 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Créer line ou rajoute un maillon a line
*/

void	minishell_addlist(t_line *line, char *inpt)
{
	t_line	*ptr;
	int		i;
	char	**tmp;

	if (!(line && inpt))
		return ;
	tmp = ft_split_minishell(inpt, '|');
	i = -1;
	while (tmp[++i])
	{
		if (!line)
		{
			line = minishell_create_list(tmp[i]);
			if (!line)
				return ;
		}
		else
		{
			ptr = line;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = minishell_create_list(tmp[i]);
			if (!ptr->next)
				return ;
		}
	}
	ft_free_ls(tmp);
	return ;
}

/*
**	Initialisation du maillon
*/

t_line	*minishell_create_list(char *inpt)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->exec = set_line_exec(inpt);
	return (line);
}

/*
**	Met tous les attributs de line a 0
*/

t_exec	*set_list_null(t_line *line)
{
	t_exec	*tmp;

	tmp = ft_calloc(sizeof(t_exec), 1);
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->cmd = ft_strdup(inpt);
	tmp->indir = 0;
	tmp->outdir = 0;
	tmp->env = NULL;
	return (tmp);
}

void	minishell_del_list(t_line *line)
{
	t_line	*tmp;

	if (!line)
		return ;
	while (line)
	{
		tmp = line->next;
		line->next = NULL;
		if (line->cmd)
			free(line->cmd);
		free(line);
		line = tmp;
	}
}
