/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/09 18:14:36 by gsap             ###   ########.fr       */
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

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (NULL);
	line->cmd = NULL;
	if (put_env_on_line(env, line))
		return (NULL);
	line->indir = 0;
	line->outdir = 1;
	line->next = NULL;
	return (line);
}

int		put_env_on_line(t_env **env, t_line *line)
{
	t_env	*tmp;

	tmp = NULL;
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
			return (1);
	}
	return (0);
}

void	fill_line(char *cmd, t_line *ptr, char *expand, t_env **env)
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
	printf("ici\n");
	put_here_doc(&here, cmd);
	printf("ici\n");
 	bis = put_infile(&infile, expand);
	printf("bis = %d\n", bis);
	ret = check_last_indir(cmd);
	printf("ret = %d\n", ret);
	if (ret == 1)
	{
		tmp = go_to_last(&infile);
		if (!tmp)
			printf("error\n");
	}
	else if (ret == 2)
		tmp = go_to_last(&here);
	if (ret && bis != 1)
		ptr->indir = tmp->fd;
	printf("ici\n");
	ret = put_outdir(&out, &infile, bis, expand);
	if (!ret)
	{
		tmp = go_to_last(&out);
		ptr->outdir = tmp->fd;
	}
	printf("ici\n");
	expand = ft_remove_redir(cmd);
	printf("ici\n");
	ptr->cmd = ft_strdup(ft_expand(expand, env));
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
