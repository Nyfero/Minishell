/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:46:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/03 17:55:34 by gsap             ###   ########.fr       */
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
	t_dir	*here;
	t_dir	*infile;
	t_dir	*out;
	t_dir	*tmp;
	char	*expand;
	int		ret;
	int		bis;

	here = NULL;
	infile = NULL;
	out = NULL;
	put_here_doc(&here, cmd);
	expand = ft_expand(cmd, env);
 	bis = put_infile(&infile, expand);
	ret = check_last_indir(cmd);
	if (ret == 1)
		tmp = go_to_last(&infile);
	else if (ret == 2)
		tmp = go_to_last(&here);
	if (ret && !bis)
		ptr->indir = tmp->fd;
	ret = put_outdir(&out, expand);
	//if (ptr->infile)
	//	ptr->indir = write_here_doc_on_fd(ptr->infile); // si j'ai un infile ou here_doc
	/*if (!ret)
	{
		tmp = go_to_last(&out);

			ptr->outdir = tmp->fd;	//si j'ai une redirection
	}*/
	printf("tmp = %s\n", expand);
	expand = ft_remove_redir(expand, &here, &infile, &out);
	printf("expand :%s\n", expand);
	ptr->cmd = ft_strdup(expand); //cmd + arg
	return ;
}

char	*ft_remove_redir(char *expand, t_dir **here, t_dir **infile, t_dir **out)
{
	t_dir	*ptr;
	char	*tmp = NULL;
	char	*after;
	int		i;

	ptr = *here;
	/*while (ptr->next)
	{
		i = ptr->pos;
		if (!tmp)
			tmp = ft_substr(expand, 0, i);
		i += 2;
		while (expand[i] == ' ')
			i++;
		while (expand[i] && ((expand[i] != ' ' && expand[i] != '|'
				&& expand[i] != '<' && expand[i] != '>')
					|| !not_in_quotes(&expand[i])))
			i++;
		after = ft_substr(expand, i, ft_strlen(expand) - i);
		tmp = ft_strjoin_and_free_all(tmp, after);
		ptr = ptr->next;
	}
	printf("tmp = %s\n", tmp);*/
	ptr = *infile;
	while (ptr)
	{
		i = ptr->pos;
		if (!tmp)
		{
			tmp = ft_substr(expand, 0, i);
			printf("temp substr = %s\n", tmp);
		}
		while (expand[i] == '<')
			i++;
		while (expand[i] == ' ')
			i++;
		i += ptr->len_lim + 1;
		after = ft_substr(expand, i, ft_strlen(expand) - i);
		printf("after substr = %s\n", after);
		if (after)
			tmp = ft_strjoin_and_free_all(tmp, after);
		printf("temp strjoin = %s\n", tmp);
		ptr = ptr->next;
	}
	printf("tmp = %s\n", tmp);
	ptr = *out;
	while (ptr)
	{
		i = ptr->pos;
		if (!tmp)
		{
			tmp = ft_substr(expand, 0, i);
			printf("temp substr = %s\n", tmp);
		}
		while (expand[i] == '>')
			i++;
		while (expand[i] == ' ')
			i++;
		i += ptr->len_lim + 1;
		after = ft_substr(expand, i, ft_strlen(expand) - i);
		printf("after substr = %s\n", after);
		if (after)
			tmp = ft_strjoin_and_free_all(tmp, after);
		printf("temp strjoin = %s\n", tmp);
		ptr = ptr->next;
	}
	printf("tmp = %s\n", tmp);

	return (tmp);
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
		aux->next = NULL;
		aux->indir = 0;
		aux->outdir = 0;
		free(aux->cmd);
		ft_free_ls(aux->env);
		ft_free_ls(aux->path);
		free(aux);
	}
	*line = NULL;
}
