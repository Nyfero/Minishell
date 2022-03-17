/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:26:10 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/17 17:23:49 by jgourlin         ###   ########.fr       */
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

void	ft_pipex_child(t_line *arg, int *fd_pipe, int fd_in, t_pipe data)
{
	int		ret;
	char 	*temp;
	char	cwd[10000];
printf("ALPHA 1\narg->envv = ");

	data.cmd_treat = ft_split(arg->cmd, ' ');
	if (data.cmd_treat == 0)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);
	}
printf("ALPHA 2\n");
//	printf("treat A= %s\n",data.cmd_treat[0]);//suppr
	data.in = ft_pipex_check_in(arg, fd_in);
	data.out = ft_pipex_check_out(arg, fd_pipe);
	init_env(&data.env, arg->env);
	if (data.env == 0)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);
	}
printf("ALPHA 3\n");

	arg->outdir = data.out;
	arg->indir = data.in;

	if (arg->outdir == -1 || arg->indir == -1)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);
	}
printf("ALPHA 4\n");
	// EXEC BUILTIN
	ret = check_builtin(arg, &data.env);
	if (ret != -1)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit(ret);
	}
printf("ALPHA 5\n");
	//GET PATH FOR EXEC
	// . = exec
	// / = chemin depuis racine
	// autre = si path = vrai command
	// autre = si path unset = OwO marche
	// si chemin pointe dosser = bash: ./D_TEST/: Is a directory


//data.in = ft_pipex_check_in(arg, fd_in);
	if (data.in == -1 || data.out == -1)
	{
		ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
		exit (1);//exit 1
	}
printf("ALPHA 6\n");

//printf("Alpha 1\n");

	if (!ft_strncmp(data.cmd_treat[0], ".", 1) || !ft_strncmp(data.cmd_treat[0], "/", 1))
		data.path_res = 0;
	else
	{
		data.path_res = ft_pipex_path(data.cmd_treat, data.path);
	//	if (!data.path || !data.path[0])
	//	{
	//		printf("! data path\n");//a suppr
	//	}

//	printf("data.path_res = %s\n", data.path_res);
		if (!data.path_res)
		{
			if (!getcwd(cwd, sizeof(cwd)))
			{
				printf("getcwd() error\n");
				exit (1);
			}
			temp = ft_strjoin(cwd, "/");
			if (!temp)
				exit (1);
			data.path_res = ft_strjoin_and_free_s1(temp, data.cmd_treat[0]);
			if (!data.path_res)
				exit (1);
			if (!access(temp, F_OK) && !data.path)//check si dans dossier si oui passer comme '.' '/'
			{// exactement pareil que cas '.' '/'
//				printf("path unset mais cmd trouver\n");//a suppr
				if (ft_file_access(data.cmd_treat[0]) == -1)
				{
					printf("bash: %s: Is a directory\n", data.cmd_treat[0]);//modif
					ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
					exit (126);
				}
				else if (ft_file_access(data.cmd_treat[0]) == 0)
				{
					printf("bash: %s: No such file or directory\n", data.cmd_treat[0]);//mettre bon message erreur sur bonne sortie
					ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
					exit (127);
				}
				else if (access(data.cmd_treat[0] , F_OK | X_OK))
				{
					printf("bash: %s: Permission denied\n", data.cmd_treat[0]);//modif
					ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
					exit (126);
				}

			}
			else if (access(data.path_res, F_OK))
			{
				printf("bash: %s: No such file or directory\n", data.cmd_treat[0]);//mettre bon message erreur sur bonne sortie
				ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
				exit (127);
			}

		}
		else if (data.path && data.path_res == 0)
		{
			printf("bash: %s: Command not found\n", data.cmd_treat[0]);//modifier
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (127);
		}
//		printf("path set\n");//a suppr
	}

//printf("Alpha 1.b\n");//suppr


//printf("Alpha 2\n");//suppr
	if (!ft_strncmp(data.cmd_treat[0], ".", 1) || !ft_strncmp(data.cmd_treat[0], "/", 1))
	{
		if (ft_file_access(data.cmd_treat[0]) == -1)
		{
			printf("bash: %s: Is a directory\n", data.cmd_treat[0]);//modif
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (126);
		}
		else if (ft_file_access(data.cmd_treat[0]) == 0)
		{
			printf("bash: %s: No such file or directory\n", data.cmd_treat[0]);//mettre bon message erreur sur bonne sortie
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (127);
		}
		else if (access(data.cmd_treat[0] , F_OK | X_OK))
		{
			printf("bash: %s: Permission denied\n", data.cmd_treat[0]);//modif
			ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
			exit (126);
		}
	}

//printf("Alpha 3\n");

	dup2(data.out, 1);
	dup2(data.in, 0);

	ft_pipex_close(fd_pipe, fd_in, &data);
//int i = 0;//suppr
//i = 0;//suppr
//while (data.cmd_treat[i])//suppr
//	printf("end data.cmd_treat= %s\n", data.cmd_treat[i++]);//suppr
//printf("EXEC\n");//a suppr

if (!ft_strncmp(data.cmd_treat[0], ".", 1) || !ft_strncmp(data.cmd_treat[0], "/", 1))
	execve(data.cmd_treat[0], data.cmd_treat, arg->env);
execve(data.path_res, data.cmd_treat, arg->env);

ft_pipex_clean(&arg, &data, fd_pipe, fd_in);
exit(1);

}

// gerer a.out
// /mnt/nfs/homes/jgourlin/Exercice/Cercle_4/Minishell/minishell/a.out
