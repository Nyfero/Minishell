/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:00:25 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/22 11:19:31 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	char			*infile;
//	char			*outfile;
//	char			*cmd;		cmd avec flags etc
//	int				indir;		
//	int				outdir;
//	char			**env;
//	struct s_line	*next;

//cat Makefile > ok | grep clean   mettre le cat dans ok et grep ce qui q ete mis (pas le droit de read)

void	ft_pipex_init(t_line *arg)
{
	*cmd;

	arg->indir = 0;
	arg->outdir = 1;
	if (arg->infile)
		arg->indir = -1;
	if (arg->outfile && arg->next == 0)
		arg->outdir = -1;
	//else if (arg->outfile && arg->next != 0)
	//	faire un dup2

	char			**env;
	struct s_line	*next;
}

int	ft_pipex(t_line *arg, int step)
{

}

int	pipex_entry(t_line *arg)
{
	//check arg
	ft_pipex_init(arg);
	ft_pipex(arg, 0); //t_line, int step
	//return reussite ou numero erreur
}
