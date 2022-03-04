/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/04 19:13:49 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list_line(t_line **line, int len, t_env **env)
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
	t_env	*tmp;

	tmp = NULL;
	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (NULL);
	line->cmd = NULL;
	if (!*env)
		line->env = NULL;
	else
	{
		line->env = env_to_str(env);
		tmp = ft_get_var("PATH", *env);
	}
	if (!tmp)
		line->path = NULL;
	else
	{
		line->path = ft_split(tmp->var, ':');
		if (!line->path)
			return (NULL);
	}
	line->indir = 0;
	line->outdir = 0;
	line->next = NULL;
	return (line);
}

void	fill_line(char *cmd, t_line *ptr, char *expand)
{
	t_dir	*here;
	t_dir	*infile;
	t_dir	*out;
	t_dir	*tmp;
	int		ret;
	int		bis;

	here = NULL;
	infile = NULL;
	out = NULL;
	put_here_doc(&here, cmd);
 	bis = put_infile(&infile, expand);
	ret = check_last_indir(cmd);
	if (ret == 1)
		tmp = go_to_last(&infile);
	else if (ret == 2)
		tmp = go_to_last(&here);
	if (ret && !bis)
		ptr->indir = tmp->fd;
	ret = put_outdir(&out, &infile, bis, expand);
	if (!ret)
	{
		tmp = go_to_last(&out);
		ptr->outdir = tmp->fd;
	}
	expand = ft_remove_redir(expand, &here, &infile, &out);
	ptr->cmd = ft_strdup(expand);
	return ;
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
		aux->indir = 0;
		aux->outdir = 0;
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
