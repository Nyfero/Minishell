/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/21 15:40:51 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_init(int *fd)
{
	fd[0] = 0;
	fd[1] = 0;
	if (pipe(fd) == -1)
		return (1);
	return (0);
}

int	ft_pipex(t_line *arg, int fd_in, t_pipe data)
{
	pid_t	child;
	int		fd[2];
	int		status;
	int		ret;

	if (ft_pipex_init(fd))
		return (1);
	child = fork();
	if (child == -1)
	{
		ft_pipex_close(fd, fd_in, 0);
		return (1);
	}
	if (child == 0)
		ft_pipex_child(arg, fd, fd_in, data);
	if (fd_in > 0)
		close(fd_in);
	close(fd[1]);
	if (arg->next)
		ret = ft_pipex(arg->next, fd[0], data);
	close(fd[0]);
	waitpid(child, &status, 0);
	if (!arg->next)
		ret = WEXITSTATUS(status);
	return (ret);
}

void	pipex_entry_init(t_pipe *data, t_env **env)
{
	data->real_env = *env;
	data->env = 0;
	data->path = 0;
	data->out = -1;
	data->in = -1;
	data->path_res = 0;
	data->cmd_treat = 0;
	signal_child();
}

int	pipex_entry(t_line *arg, t_env **env)
{
	t_pipe	data;
	t_env	*res;
	int		ret;

	pipex_entry_init(&data, env);
	if (!arg->next)
	{
		ret = check_builtin(arg, env);
		if (ret != -1)
			return (ret);
	}
	if (*env)
	{
		res = ft_get_var("PATH", *env);
		if (res && res->var)
		{
			data.path = ft_split(res->var, ':');
			if (!data.path)
				return (1);
		}
	}
	ret = ft_pipex(arg, 0, data);
	if (data.path)
		ft_free_ls(data.path);
	return (ret);
}
