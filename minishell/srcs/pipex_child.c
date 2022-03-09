/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:26:10 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/09 16:14:43 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ft_pipex_close(int *fd, int fd_in, t_pipe data)
{
	close(fd[0]);
	close(fd[1]);
	if (fd_in > 0)
		close(fd_in);
	if (data.in > 2)
		close(data.in);
	if (data.out > 2)
		close(data.out);
	return (0);
}
*/

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
	//check built in
//printf("ft_pipex_path = 0\n");
	if (!path || path[0] == 0)
	{
	//	printf("bash: %s: No such file or directory\n", temp_cmd[0]);//mettre bon message erreur sur bonne sortie
		return (0);
	}
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
		{
		//	printf("PATH = %s\n", res);
			return (res);
		}
		free(res);
		i++;
	}
	return (0);
}

void	ft_pipex_child(t_line *arg, int *fd_pipe, int fd_in, t_pipe data)
{
	int		ret;
	t_env *test;

	test = 0;
	data.cmd_treat = ft_split(arg->cmd, ' ');
	if (data.cmd_treat == 0)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);
	}
	printf("treat A= %s\n",data.cmd_treat[0]);
	int i = -1;
	data.in = ft_pipex_check_in(arg, fd_in);
	data.out = ft_pipex_check_out(arg, fd_pipe);
	printf("ALPHA %s\n", "lol" );
	printf("treat[0][0] B= %d\n",data.cmd_treat[0][0]);
	printf("ALPHA %s\n", "lol" );
	init_env(&test, arg->env);
	if (test == 0)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);
	}

	arg->outdir = data.out;
	arg->indir = data.in;

	if (arg->outdir == -1 || arg->indir == -1)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);
	}
	printf("avant buit\n");
	ret = check_builtin(arg, &test);
	if (ret != -1)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit(ret);
	}
		printf("treat C= %s\n",data.cmd_treat[0]);

	char	cwd[10000];
	data.path_res = ft_pipex_path(data.cmd_treat, data.path);
	printf("path = %s\n", data.path_res );
	if (!data.path_res)
	{
		printf("0\n");
		if (!getcwd(cwd, sizeof(cwd)))
		{
			printf("8\n");
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (127);
		}
		char *temp;
		temp = ft_strjoin(cwd, "/");
		printf("temp= %s\ntreat = %s\n",temp,  data.cmd_treat[0]);
		if (!access(data.cmd_treat[0], F_OK | X_OK))
			data.path_res = ft_strjoin_and_free_s1(temp, data.cmd_treat[0]);
		if (!data.path_res)
		{
			if (!data.path || data.path[0] == 0)		
				printf("bash: %s: No such file or directory\n", data.cmd_treat[0]);//mettre bon message erreur sur bonne sortie
			else
				printf("bash: %s: Command not found\n", data.cmd_treat[0]);//mettre bon message erreur sur bonne sortie
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (2);
		}
	}
	printf("8\n");
//data.in = ft_pipex_check_in(arg, fd_in);
	if (data.in == -1 || data.out == -1)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (3);
	}
	dup2(data.out, 1);
	dup2(data.in, 0);

	ft_pipex_close(fd_pipe, fd_in, &data);
//execve(data.path_res, data.cmd_treat, arg->env);
i = 0;
while (data.cmd_treat[i])
	printf("data.cmd_treat= %s\n", data.cmd_treat[i++]);
execve(data.path_res, data.cmd_treat, arg->env);

ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
exit(1);

}
