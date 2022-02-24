/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:26:10 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/22 18:02:39 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_close(int *fd, int fd_in, int *temp, int in)
{
	close(fd[0]);
	close(fd[1]);
	if (fd_in > 0)
		close(fd_in);
	if (temp[0] > 2)
		close(temp[0]);
	if (temp[1] > 2)
		close(temp[1]);
	if (in > 2)
		close(in);
	return (0);
}

int	ft_pipex_check_in(t_line *arg, int fd_in, int *temp)
{
	int	i;

	i = 0;
	temp[0] = 0;
	temp[1] = 0;
	//check et recup path aboslue ou si build in maison
	//en fonciton gerer le in
	//priorite de < << sur entree fd_in
	if (arg->indir == 0)
	{
		return (fd_in);
		//lire depuis de fd
		//rien a faire ? 1er jsp, les autres recoient normal (fd[0])
	}
	if (arg->indir == 1)
	{
		//verifier si fichier existe, ou pas ? voir si open le fait solo
		//open infile et dup2 file dans 0
		return (open(arg->outfile, O_RDONLY));
	}
	if (arg->indir == 2)
	{
		if (pipe(temp) == -1)
		{
			printf("problem ici \n");
			return (-1);
		}
		//infile = input
		//creation pipe avant ensuite rediriger str dans dams fd[1]
		//passer fd[1] en 0
		while (arg->outfile[i])
			write(temp[1], arg->outfile + i++, 1);
		return (temp[0]);
	}
	return (0);
}

int	ft_pipex_check_out(t_line *arg, int *fd)
{
	if (arg->outdir == 0)
	{
		if (arg->next == 0)
			return (1);
		else
			return (fd[1]);
		//ecrire sortie standard / sortie vers next pipe
		return (0);
	}
	if (arg->outdir == 1)
		return (open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (arg->outdir == 2)
		return (open(arg->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644));
	//ici
	printf("test etrange, a supprimer\n");
	//sdfss
	return (-1);

}

void	ft_pipex_child(t_line *arg, int *fd, int fd_in)
{
	int out;
	int	in;
	int	temp[2];

	//verifier path cmd / si existe  err 127
	//verif entree , path , redir entry
	//verif sortie , redir exit
	in = ft_pipex_check_in(arg, fd_in, temp);
	if (in == -1)
	{
		printf("%s : %s\n", arg->outfile, strerror(errno));
		ft_pipex_close(fd, fd_in, temp, in);
		exit (1);
	}
	out = ft_pipex_check_out(arg, fd);
	if (out == -1)
	{
		printf("%s : %s\n", arg->outfile, strerror(errno));
		ft_pipex_close(fd, fd_in, temp, in);
		exit (1);
	}
	dup2(out, 1);//dup2 sortie
	dup2(fd_in, 0);

	ft_pipex_close(fd, fd_in, temp, in);
	if (out > 2)
		close (out);
	//close les fd
	//execve
	//propre
}