/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:26:10 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/21 14:32:55 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_check_in(t_line *arg, int fd_in)
{
	if (!arg->indir)
		return (fd_in);
	if (arg->indir)
		return (arg->indir);
	return (0);
}

int	ft_pipex_check_out(t_line *arg, int *fd)
{
	if (arg->outdir == 1)
	{
		if (arg->next == 0)
			return (1);
		else
			return (fd[1]);
		return (0);
	}
	if (arg->outdir)
		return (arg->outdir);
	return (-1);
}

char	*ft_pipex_path(char **temp_cmd, char **path)
{
	int		i;
	char	*test;
	char	*res;

	i = 0;
	if (!path || path[0] == 0)
		return (0);
	while (path[i])
	{
		test = ft_strjoin(path[i], "/");
		if (!test)
			return (0);
		res = ft_strjoin(test, temp_cmd[0]);
		free(test);
		if (!res)
			return (0);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (0);
}

/*
**GET PATH FOR EXEC
** . = exec
** / = chemin depuis racine
** autre = si path = vrai command
** autre = si path unset = OwO marche
** si chemin pointe dosser = bash: ./D_TEST/: Is a directory
**
*/

void	ft_pipex_nopath(t_line **arg, t_pipe *data, int fd_in, int *fd_pipe)
{
	char	*temp;
	char	cwd[10000];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	temp = ft_strjoin(cwd, "/");
	if (!temp)
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	data->path_res = ft_strjoin_and_free_s1(temp, data->cmd_treat[0]);
	if (!data->path_res)
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	if (!access(data->path_res, F_OK) && !data->path)
		ft_pipex_check_cmd(*arg, data, fd_in, fd_pipe);
	else if (access((*data).path_res, F_OK))
	{
		printf("bash: %s: No such file or directory\n", data->cmd_treat[0]);//mettre bon message erreur sur bonne sortie
		ft_pipex_clean(arg, data, fd_pipe, fd_in);
		exit (127);
	}
}

void	ft_pipex_child(t_line *arg, int *fd_pipe, int fd_in, t_pipe data)
{
	ft_child_check_arg(&arg, &data, fd_pipe, fd_in);
	if (!ft_strncmp(data.cmd_treat[0], ".", 1) || !ft_strncmp(data.cmd_treat[0], "/", 1))
		ft_pipex_check_cmd(arg, &data, fd_in, fd_pipe);
	else
	{
		data.path_res = ft_pipex_path(data.cmd_treat, data.path);
		if (!data.path)
		{
			ft_pipex_nopath(&arg, &data, fd_in, fd_pipe);
		}
		else if (data.path && data.path_res == 0)
		{
			printf("bash: %s: Command not found\n", data.cmd_treat[0]);//modifier
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (127);
		}
	}
	dup2(data.out, 1);
	dup2(data.in, 0);
	ft_pipex_close(fd_pipe, fd_in, &data);
	if (!ft_strncmp(data.cmd_treat[0], ".", 1) || !ft_strncmp(data.cmd_treat[0], "/", 1))
		execve(data.cmd_treat[0], data.cmd_treat, arg->env);
	execve(data.path_res, data.cmd_treat, arg->env);
	ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
	exit(1);
}
