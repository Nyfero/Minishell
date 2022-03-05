/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/05 14:22:04 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si next == 0 pas de dup2
//child ont leur propre env
//si build in envoyer copie factice de env

//void	ft_pipex_init(t_line *arg)
//{
//
//}

int	ft_pipex(t_line *arg, int fd_in, char **path)
{
	pid_t	child;
	int		fd[2];
	int		status;
	int		ret;

	child = -1;
	status = 0;
	if (pipe(fd) == -1)//creation du pipe
	{
		printf("Alpha = %s\n", strerror(errno));
		//free arg si besoin
		return (0);
	}
	child = fork();//creation child
	if (child == -1)
	{
		printf("Bravo = %s\n", strerror(errno));
		//close pipe
		//free arg si besoin
		return (0);
	}
	if (child == 0)//envoie child
	{
		ft_pipex_child(arg, fd, fd_in, path);
	}
	if (fd_in > 0)
		close(fd_in);
	close(fd[1]);

	if (arg->next)//child next
		ret = ft_pipex(arg->next, fd[0], path);

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

int	ft_parcours_env_perso(t_env *env)
{
	if (env == 0)
		return (0);
	printf("(%d) %s = %s\n", env->flags, env->name, env->var);
	if (env->next)
		ft_parcours_env_perso(env->next);
	return (0);
}

int ft_parcous_arg(t_line *arg)
{
	if (!arg)
		return (0);
	printf("cmd = %s\n", arg->cmd);
	printf("indir = %d || outdir = %d\n", arg->indir, arg->outdir);
	if (arg->next != 0)
		return (ft_parcous_arg(arg->next));
	return (0);
}

int	pipex_entry(t_line *arg, t_env **env)
{
	(void)env;

	//int i = -1;
	char	**path;
	t_env	*res;

printf("pipex entry\n");

ft_parcous_arg(arg);

printf("pipex sub_entry\n");

	path = 0;
	res = 0;
	if (!arg->next)
		printf("one command\n");//alors pas de pipe
	//ft_parcours_env_perso(*env);
	if (*env)
	{
		res = ft_get_var("PATH", *env);
		if (res)
		{
			path = ft_split(res->var, ':');
			if (!path)
			{
				printf("malloc error pipex entry 001\n");
				//Cannot allocate memory
				return (12);
			}
			int i = 0;
			while (path[i])
			{
				printf("path[%d] = %s\n", i, path[i]);
				i++;
			}
		}
	}
//printf("ALPHA %s\n", res->var);
	//check arg
	//changer char **env  pour fit avec le vrai
	int resu = 0;
	resu = ft_pipex(arg, 0, path); //t_line, int step
	printf("FIN PIPEX\n");
	return (resu);
	//return reussite ou numero erreur
}
