/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:49:56 by gsap              #+#    #+#             */
/*   Updated: 2022/03/20 20:39:58 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_line(char *cmd, t_line *ptr, t_env **env, t_garbage bin)
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
	put_here_doc(&here, cmd, bin);
	expand = ft_expand(cmd, env);
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
	ptr->cmd = del_quotes(expand);
	destroy_dir(&here);
	destroy_dir(&infile);
	destroy_dir(&out);
	free(expand);
}
