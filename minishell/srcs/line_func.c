/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/22 13:57:22 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list_line(t_line **line, int len, t_env **env)
{
	t_line	*ptr;
	int		i;

	if (len == 0)
		return ;
	i = 0;
	while (++i <= len)
	{
		if (!*line)
		{
			*line = create_line(env);
			if (!*line)
				return ;
		}
		else
		{
			ptr = *line;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = create_line(env);
			if (!ptr->next)
				return ;
		}
	}
}

t_line	*create_line(t_env **env)
{
	t_line	*line;

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (NULL);
	line->cmd = NULL;
	line->env = env_to_str(env);
	line->path = NULL;
	line->indir = 0;
	line->outdir = 1;
	line->next = NULL;
	return (line);
}

void	destroy_list_line(t_line **line)
{
	t_line	*ptr;
	t_line	*aux;

	ptr = *line;
	while (ptr != NULL)
	{
		aux = ptr;
		ptr = ptr->next;
		aux->next = NULL;
		if (aux->indir > 0)
			close(aux->indir);
		if (aux->outdir > 1)
			close(aux->outdir);
		if (aux->cmd)
			free(aux->cmd);
		if (aux->env)
			ft_free_ls(aux->env);
		if (aux->path)
			ft_free_ls(aux->path);
		free(aux);
	}
	*line = NULL;
}
