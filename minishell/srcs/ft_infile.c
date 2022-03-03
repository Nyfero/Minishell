/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:01:52 by gsap              #+#    #+#             */
/*   Updated: 2022/03/03 17:36:21 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_infile(t_dir **infile, char *cmd)
{
	int		i;
	int		compt;
	t_dir	*ptr;

	i = -1;
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '<')
		{
			i++;
			compt++;
		}
		if (compt == 1)
		{
			if (!*infile)
			{
				*infile = create_infile_maillon(cmd, i);
				if (!*infile || (*infile)->fd == -1)
					return (1);
			}
			else
			{
				ptr = go_to_last(infile);
				close(ptr->fd);
				ptr->next = create_infile_maillon(cmd, i);
				if (!ptr->next || ptr->next->fd == -1)
					return (1);
			}
		}
	}
	return (0);
}

t_dir	*create_infile_maillon(char *cmd, int i)
{
	char 	*lim;
	t_dir	*tmp;

	tmp = ft_calloc(sizeof(t_dir), 1);
	if (!tmp)
		return (NULL);
	tmp->pos = i - 2;
	tmp->next = NULL;
	lim = grep_indir(&cmd[i - 2]);
	if (!lim)
	{
		tmp->fd = -1;
		return (tmp);
	}
	tmp->len_lim = ft_strlen(lim);
	if (check_infile_access(lim))
	{
		tmp->fd = -1;
		return (tmp);
	}
	tmp->fd = open(lim, O_RDONLY);
	if (tmp->fd == -1)
		perror("open");
	free(lim);
	return (tmp);
}

int		check_infile_access(char *lim)
{
	if (ft_file_access(lim) == 0)
	{
		ft_putstr_fd(lim, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(lim);
		return (1);
	}
	if (ft_file_access(lim) == -1)
	{
		ft_putstr_fd(lim, 2);
		if (access(lim, F_OK | R_OK))
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": is a directory\n", 2);
		free(lim);
		return (1);
	}
	return (0);
}
