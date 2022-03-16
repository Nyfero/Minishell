/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/16 13:32:43 by gsap             ###   ########.fr       */
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

void	fill_line(char *cmd, t_line *ptr, t_env **env)
{
	t_dir	*here;
	t_dir	*infile;
	t_dir	*out;
	t_dir	*tmp;
	char	*expand;
	int		ret;
	int		bis;

	(void)env;
	here = NULL;
	infile = NULL;
	out = NULL;
	put_here_doc(&here, cmd);
	printf("first expand :%s\n", cmd);
	expand = ft_expand(cmd, env);
	printf("end expand :%s\n", expand);
 	bis = put_infile(&infile, expand);
	ret = check_last_indir(cmd);
	if (ret)
	{
		if (ret == 1)
			tmp = go_to_last(&infile);
		else
			tmp = go_to_last(&here);
		if (!tmp)
			ptr->indir = -1;
	}
	if (ret && bis != 1)
		ptr->indir = tmp->fd;
	ret = put_outdir(&out, &infile, bis, expand);
	if (!ret)
	{
		tmp = go_to_last(&out);
		ptr->outdir = tmp->fd;
	}
	expand = ft_remove_redir(expand);
	printf("second expand :%s\n", expand);
	ptr->cmd = del_quotes(expand);
	printf("ptr->cmd:%s\n", ptr->cmd);
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
