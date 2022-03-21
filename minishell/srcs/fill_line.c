/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:49:56 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 13:50:39 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_line(char *cmd, t_line *ptr, t_env **env, t_garbage bin)
{
	char	*expand;
	t_dir	*infile;
	t_dir	*tmp;
	int		out;

	infile = NULL;
	expand = ft_expand(cmd, env);
	bin.expand = expand;
	ptr->indir = place_indir(cmd, expand, bin, &infile);
	tmp = go_to_last(&infile);
	out = put_outdir(tmp, expand);
	if (out != -1)
		ptr->outdir = out;
	expand = ft_remove_redir(expand);
	ptr->cmd = del_quotes(expand);
	destroy_dir(&infile);
}

int	place_indir(char *cmd, char	*expand, t_garbage bin, t_dir **infile)
{
	t_dir	*ptr;
	int		here;
	int		last_indir;
	int		good_infile;

	ptr = NULL;
	here = put_here_doc(cmd, bin);
	good_infile = put_infile(infile, expand);
	last_indir = check_last_indir(cmd);
	ptr = go_to_last(infile);
	if (!ptr && good_infile)
		return (-1);
	if (last_indir)
	{
		if (last_indir == 1)
		{
			if (here)
				close(here);
			here = ptr->fd;
		}
		else if (ptr)
			close(ptr->fd);
	}
	return (here);
}
