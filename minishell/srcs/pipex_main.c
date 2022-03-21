/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/21 14:56:41 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;
/*
**	ctr + c
**	return 130
*/

void	handle_sigint_2(int sig)
{
	(void)sig;
	g_sig = 130;
}

/*
**	ctr + \
**	^\Quit (core dumped) dans child
**	return 131
*/

void	handle_sigquit_2(int sig)
{
	(void)sig;
	g_sig = 131;
}

void	init_signal_2(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	if (sigemptyset(&sint.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	if (sigemptyset(&squit.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	sint.sa_handler = &handle_sigint_2;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = &handle_sigquit_2;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}

/*
int	ft_parcours_env_perso(t_env *env)//asuppra la fin
{
	if (env == 0)
		return (0);
	printf("(%d) %s = %s\n", env->flags, env->name, env->var);
	if (env->next)
		ft_parcours_env_perso(env->next);
	return (0);
}

int ft_parcous_arg(t_line *arg)//a suppr a la fin
{
	if (!arg)
		return (0);
	printf("cmd = %s\n", arg->cmd);
	printf("indir = %d || outdir = %d\n", arg->indir, arg->outdir);
	if (arg->next != 0)
		return (ft_parcous_arg(arg->next));
	return (0);
}
*/

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
	data->in= -1;
	data->path_res = 0;
	data->cmd_treat = 0;
	init_signal_2();
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
