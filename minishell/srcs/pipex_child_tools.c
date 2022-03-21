/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:46:01 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/21 14:35:18 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_check_cmd(t_line *arg, t_pipe *data, int fd_in, int *fd_pipe)
{
	if (ft_file_access(data->cmd_treat[0]) == -1)
	{
		printf("bash: %s: Is a directory\n", data->cmd_treat[0]);//modif
		ft_pipex_clean(&arg, data, fd_pipe, fd_in);
		exit (126);
	}
	else if (ft_file_access(data->cmd_treat[0]) == 0)
	{
		printf("bash: %s: No such file or directory\n", data->cmd_treat[0]);//mettre bon message erreur sur bonne sortie
		ft_pipex_clean(&arg, data, fd_pipe, fd_in);
		exit (127);
	}
	else if (access(data->cmd_treat[0], F_OK | X_OK))
	{
		printf("bash: %s: Permission denied\n", data->cmd_treat[0]);//modif
		ft_pipex_clean(&arg, data, fd_pipe, fd_in);
		exit (126);
	}
}

void	ft_pipex_child_exit_1(t_line **arg, t_pipe *data, int fd, int *fd_pipe)
{
	ft_pipex_clean(arg, data, fd_pipe, fd);
	exit (1);
}

void	ft_child_check_arg(t_line **arg, t_pipe *data, int *fd_pipe, int fd_in)
{
	int	ret;

	data->cmd_treat = ft_split((*arg)->cmd, ' ');
	if (data->cmd_treat == 0)
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	(*data).in = ft_pipex_check_in(*arg, fd_in);
	(*data).out = ft_pipex_check_out(*arg, fd_pipe);
	if (ft_cpy_env(&data->env, data->real_env))
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	if (data->env == 0)
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	(*arg)->outdir = data->out;
	(*arg)->indir = data->in;
	if ((*arg)->outdir == -1 || (*arg)->indir == -1)
		ft_pipex_child_exit_1(arg, data, fd_in, fd_pipe);
	ret = check_builtin(*arg, &data->env);
	if (ret != -1)
	{
		ft_pipex_clean(arg, data, fd_pipe, fd_in);
		exit(ret);
	}
}
