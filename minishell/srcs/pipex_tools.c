/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:16:57 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/17 15:41:22 by jgourlin         ###   ########.fr       */
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

printf("bravo 1\n");

	ft_pipex_close(fd, fd_in, data);
	i = 0;
	if (data->path_res)
		free(data->path_res);
printf("bravo 2\n");
	if (data->path)
	{
		while (data->path[i])
			free(data->path[i++]);
		free(data->path);
	}
printf("bravo 3\n");
	i = 0;
	if (data->cmd_treat)
	{
		while (data->cmd_treat[i])
			free(data->cmd_treat[i++]);
		free(data->cmd_treat);
	}
	if (data->env)
		destroy_env(&data->env);
printf("bravo 4\n");
	destroy_list_line(arg);
printf("bravo 5\n");
	return (0);
}
