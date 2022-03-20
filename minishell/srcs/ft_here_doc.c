/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/20 20:23:54 by gsap             ###   ########.fr       */
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

printf("papa ptrcmd = %p (%s)\n",bin.cmd, bin.cmd[0]);
printf("papa ptrbin = %p\n", &bin);
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
			break;
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

void	put_here_doc(t_dir **here, char *cmd, t_garbage bin)
{
	int		i;
	int		compt;

	i = -1;
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
			compt = create_here_list(here, cmd, i, bin);
			if (compt)
				return ;
		}
		else if (compt > 2 && bool_not_in_quotes(&cmd[i]))
		{
			ft_putendl_fd("syntax error near unexpected token `<'", 2);
			return ;
		}
	}
}

int	create_here_list(t_dir **here, char *cmd, int i, t_garbage bin)
{
	t_dir	*ptr;

	bin.here = here;
	if (!*here)
	{
		*here = create_here_maillon(cmd, i, bin);
		if (!*here || (*here)->fd == -1)
			return (1);
	}
	else
	{
		ptr = go_to_last(here);
		close(ptr->fd);
		ptr->next = create_here_maillon(cmd, i, bin);
		if (!ptr->next || ptr->next->fd == -1)
			return (1);
	}
	return (0);
}

t_dir	*create_here_maillon(char *cmd, int i, t_garbage bin)
{
	char	*lim;
	t_dir	*tmp;

	tmp = ft_calloc(sizeof(t_dir), 1);
	if (!tmp)
		return (NULL);
	tmp->fd = -1;
	tmp->next = NULL;
	lim = get_limiteur(&cmd[i]);
	if (!lim)
		return (tmp);
	bin.cur_here = tmp;
	tmp->fd = write_here_doc_on_fd(lim, bin);
	free(lim);
	return (tmp);
}
