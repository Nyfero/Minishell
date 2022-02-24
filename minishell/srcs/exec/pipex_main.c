/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/24 17:48:36 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	char			*infile;	si heredoc aors string direct
//	char			*outfile;
//	char			*cmd;		cmd avec flags etc
//	int				indir;
//	int				outdir;
//	char			**env;
//	struct s_line	*next;

//cat Makefile > ok | grep clean   mettre le cat dans ok et grep ce qui q ete mis (pas le droit de read)

//si next == 0 pas de dup2
//child ont leur propre env
//si build in envoyer copie factice de env

//void	ft_pipex_init(t_line *arg)
//{
//
//}

int	ft_pipex(t_line *arg, int fd_in)
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
		exit(0);
	}
	child = fork();//creation child
	if (child == -1)
	{
		printf("Bravo = %s\n", strerror(errno));
		//free arg si besoin
		exit (0);
	}
	if (child == 0)//envoie child
	{
		ft_pipex_child(arg, fd, fd_in);
	}
	if (fd_in > 0)
		close(fd_in);
	close(fd[1]);

	if (arg->next)//child next
		ret = ft_pipex(arg->next, fd[0]);

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
	(void)env;
	//check arg
	//ft_pipex_init(arg);
	//changer char **env  pour fit avec le vrai
	return (ft_pipex(arg, 0)); //t_line, int step
	//return reussite ou numero erreur
}
