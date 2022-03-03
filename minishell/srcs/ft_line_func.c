/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/03 15:06:29 by gsap             ###   ########.fr       */
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

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (NULL);
	line->infile = NULL;
	line->outfile = NULL;
	line->cmd = NULL;
	line->env = env_to_str(env);
	tmp = ft_get_var("PATH", *env);
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

void	fill_line(char *cmd, t_line *ptr, t_env **env)
{
	t_in	*here;
	t_in	*infile;
	t_in	*tmp;
	char	*expand;
	int		ret;
	int		bis;

	here = NULL;
	infile = NULL;
	put_here_doc(&here, cmd);
	expand = ft_expand(cmd, env);
 	bis = put_infile(&infile, expand, env);
	ret = check_last_indir(cmd);
	if (ret == 1)
		tmp = go_to_last(&infile);
	else if (ret == 2)
		tmp = go_to_last(&here);
	if (ret && !bis)
		ptr->indir = tmp->fd;

	//if (ptr->infile)
	//	ptr->indir = write_here_doc_on_fd(ptr->infile); // si j'ai un infile ou here_doc

	ptr->outdir = 0;	//si j'ai une redirection
	ptr->cmd = ft_strdup(expand); //cmd + arg
	return ;
}

/*
**	verifier que tous les mallocs sont bien detruits
*/

void	destroy_list_line(t_line **line)
{
	t_line	*ptr;
	t_line	*aux;

	ptr = *line;
	while (ptr != NULL)
	{
		aux = ptr;
		ptr = ptr->next;
		free(aux->cmd);
		ft_free_ls(aux->env);
		ft_free_ls(aux->path);
		free(aux);
	}
	*line = NULL;
}
