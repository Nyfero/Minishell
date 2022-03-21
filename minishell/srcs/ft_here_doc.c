/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 17:38:32 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ouvre un pipe et écrit le here doc dedans puis renvoie fd[0]
*/

int	write_here_doc_on_fd(char *lim, t_garbage bin)
{
	int		fd[2];
	pid_t	child;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	child = fork();
	if (child == -1)
		return (-1);
	if (!child)
	{
		signal_here();
		get_here_doc(lim, fd);
		free_bin(bin);
		exit(0);
	}
	signal_child();
	wait(&child);
	signal_main();
	close(fd[1]);
	return (fd[0]);
}

void	get_here_doc(char *lim, int fd[2])
{
	char	*line;
	int		i;
	int		x;

	x = 1;
	while (1)
	{
		line = readline("here_doc> ");
		if (!line)
			return (warning_here_doc(lim, x));
		x++;
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
			break ;
		i = 0;
		while (line[i])
			write(fd[1], line + i++, 1);
		write(fd[1], "\n", 1);
		free(line);
	}
	free(lim);
	free(line);
	close(fd[1]);
	close(fd[0]);
}

int	put_here_doc(char *cmd, t_garbage bin)
{
	int	i;
	int	compt;
	int	here;

	i = -1;
	here = 0;
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '<' && bool_not_in_quotes(&cmd[i]))
		{
			i++;
			compt++;
		}
		if (compt == 2)
		{
			here = create_here(here, cmd, i, bin);
			if (here <= 0)
				return (-2);
		}
		else if (compt > 2 && bool_not_in_quotes(&cmd[i]))
			return (print_error_syntax(0));
	}
	return (here);
}

int	create_here(int here, char *cmd, int i, t_garbage bin)
{
	char	*lim;

	if (here)
		close(here);
	lim = get_limiteur(&cmd[i]);
	if (!lim)
		return (-1);
	here = write_here_doc_on_fd(lim, bin);
	free(lim);
	return (here);
}
