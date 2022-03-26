/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/26 18:04:25 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*ft_pipex_destroy_actual_line(t_line **arg)
{
	t_line	*ptr;
	t_line	*ret;

	ptr = *arg;
	ret = ptr->next;
	if (ptr->cmd)
		free (ptr->cmd);
	if (ptr->env)
		ft_free_ls(ptr->env);
	if (ptr->indir > 1)
		close(ptr->indir);
	if (ptr->outdir > 2)
		close(ptr->outdir);
	ptr->next = 0;
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ret);
}

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
	t_line	*test;

	if (ft_pipex_init(fd))
		return (1);
	child = fork();
	if (child == -1)
		return (ft_pipex_close(fd, fd_in, 0));
	if (child == 0)
		ft_pipex_child(arg, fd, fd_in, data);
	if (fd_in > 0)
		close(fd_in);
	close(fd[1]);
	test = ft_pipex_destroy_actual_line(&arg);
	if (test)
		ret = ft_pipex(test, fd[0], data);
	close(fd[0]);
	waitpid(child, &status, 0);
	if (!test)
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
		ret = check_builtin(arg, env, 0);
		if (ret != -1)
			return (ft_pipex_free_return(arg, ret));
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
