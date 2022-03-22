/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:49:56 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 20:06:34 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_line(char *cmd, t_line *ptr, t_env **env, t_garbage bin)
{
	char	*expand;
	t_dir	*infile;

	infile = NULL;
	expand = ft_expand(cmd, env);
	if (!expand)
		expand = NULL;
	bin.expand = expand;
	ptr->indir = place_indir(cmd, expand, bin, &infile);
	if (ptr->indir == -2)
	{
		if (expand)
			free(expand);
		destroy_dir(&infile);
		return (1);
	}
	ptr->outdir = place_outdir(expand, infile);
	if (ptr->outdir == -2)
	{
		free(expand);
		return (1);
	}
	ptr->cmd = place_cmd(expand);
	if (!ptr->cmd)
		return (1);
	return (0);
}

int	place_indir(char *cmd, char	*expand, t_garbage bin, t_dir **infile)
{
	t_dir	*ptr;
	int		here;
	int		last_indir;
	int		good_infile;

	here = put_here_doc(cmd, bin);
	if (here == -2)
		return (here);
	good_infile = put_infile(infile, expand);
	if (good_infile == 2)
	{
		if (here != 0)
			close (here);
		return (-2);
	}
	last_indir = check_last_indir(cmd);
	ptr = go_to_last(infile);
	if (!ptr && good_infile)
		return (-1);
	if (last_indir == 1)
	{
		if (here > 0)
			close(here);
		here = ptr->fd;
	}
	else if (last_indir == 2 && ptr)
		close(ptr->fd);
	return (here);
}

int	place_outdir(char *expand, t_dir *infile)
{
	t_dir	*tmp;
	int		out;

	tmp = go_to_last(&infile);
	if (infile && infile->fd == -1)
		out = put_outdir_upto_last_indir(1, infile, expand);
	else
		out = put_outdir(expand);
	destroy_dir(&infile);
	return (out);
}

char	*place_cmd(char *expand)
{
	char	*tmp;

	expand = ft_remove_redir(expand);
	if (!expand)
		return (NULL);
	tmp = del_quotes(expand);
	if (!tmp[0])
	{
		ft_putendl_fd("bash: : command not found", 2);
		return (NULL);
	}
	return (tmp);
}
