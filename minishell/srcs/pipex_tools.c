/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:16:57 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/10 14:22:53 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_close(int *fd, int fd_in, t_pipe *data)
{
	close(fd[0]);
	close(fd[1]);
	if (fd_in > 0)
		close(fd_in);
	if (data->in > 2)
		close(data->in);
	if (data->out > 2)
		close(data->out);
	return (0);
}

int	ft_pipex_clean(t_line **arg, t_pipe *data, int *fd, int fd_in)
{
	int	i;

	ft_pipex_close(fd, fd_in, data);
	i = 0;
	if (data->path_res)
		free(data->path_res);
	if (data->path)
	{
		while (data->path[i])
			free(data->path[i++]);
		free(data->path);
	}
	i = 0;
	if (data->cmd_treat)
	{
		while (data->cmd_treat[i])
			free(data->cmd_treat[i++]);
		free(data->cmd_treat);
	}
	destroy_list_line(arg);
	return (0);
}
