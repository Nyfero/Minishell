/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/02/28 16:51:34 by gsap             ###   ########.fr       */
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
	line->env = NULL; // env_to_str
	line->path = NULL; /* res = ft_get_var("PATH", *env);
							if (res)
							path = ft_split(res->var, ':');
						*/
	line->next = NULL;
	return (line);
}

void	fill_line(char *cmd, t_line *ptr)
{
	line->indir = 0; // si j'ai un infile ou here_doc
	line->outdir = 0;	//si j'ai une redirection
	ptr->infile = NULL; // int sur le fd
	ptr->cmd = ft_strdup(cmd); //cmd + arg
	return ;
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
	}
	*line = NULL;
}
