/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/10 13:38:20 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**int	ft_parcours_env_perso(t_env *env)//asuppra la fin
**{
**	if (env == 0)
**		return (0);
**	printf("(%d) %s = %s\n", env->flags, env->name, env->var);
**	if (env->next)
**		ft_parcours_env_perso(env->next);
**	return (0);
**}
**
**int ft_parcous_arg(t_line *arg)//a suppr a la fin
**{
**	if (!arg)
**		return (0);
**	printf("cmd = %s\n", arg->cmd);
**	printf("indir = %d || outdir = %d\n", arg->indir, arg->outdir);
**	if (arg->next != 0)
**		return (ft_parcous_arg(arg->next));
**	return (0);
**}
*/

int	ft_pipex(t_line *arg, int fd_in, t_pipe data)
{
	pid_t	child;
	int		fd[2];
	int		status;
	int		ret;

	child = -1;
	status = 0;
	if (pipe(fd) == -1)//creation du pipe
	{
		//printf("Alpha = %s\n", strerror(errno));
		return (1);
	}
	child = fork();//creation child
	if (child == -1)
	{
		//printf("Bravo = %s\n", strerror(errno));
		ft_pipex_close(fd, fd_in, 0);
		return (1);
	}
	if (child == 0)//envoie child
	{
		ft_pipex_child(arg, fd, fd_in, data);
	}
	if (fd_in > 0)
		close(fd_in);
	close(fd[1]);

	if (arg->next)//child next
		ret = ft_pipex(arg->next, fd[0], data);

	close(fd[0]);
	waitpid(child, &status, 0);

	if (!arg->next)//valeur de retour fnal
	{
		ret = WEXITSTATUS(status);
	//	if (ret != 0 && access(data->file_1, R_OK) == -1)
	//		if (access(data->file_2, W_OK) == -1)
	//			ret = 1;
	}
	return (ret);
}

int	pipex_entry(t_line *arg, t_env **env)
{
	t_pipe	data;
	t_env	*res;
	int		ret;

	data.path = 0;
	data.out = -1;
	data.in= -1;
	data.path_res = 0;
	data.cmd_treat = 0;
	res = 0;
	printf("cmd pipex=%s\n", arg->cmd);
	ret = check_builtin(arg, env);
	if (!arg->next && ret != -1)
		return (ret);
	if (*env)
	{
		res = ft_get_var("PATH", *env);
		if (res)
		{
			data.path = ft_split(res->var, ':');
			if (!data.path)
			{
				printf("Cannot allocate memory\n");//a modifier
				return (1);
			}
		}
	}
	ret = ft_pipex(arg, 0, data);
	printf("FIN PIPEX\n");
	//free path;
	if (data.path)
		ft_free_ls(data.path);
	printf("ret = %d\n", ret);
	return (ret);
}
