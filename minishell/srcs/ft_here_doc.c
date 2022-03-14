/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/14 09:42:13 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ouvre un pipe et écrit le here doc dedans puis renvoie fd[0]
*/

int	write_here_doc_on_fd(char *lim)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	write(1, "here_doc>", 9);
	get_here_doc(lim, fd);
	close(fd[1]);
	return (fd[0]);
}

void	get_here_doc(char *lim, int fd[2])
{
	char	*line;
	int		i;
	int		x;

	x = 1;
	line = get_next_line(0);
	if (!line)
		return (warning_here_doc(lim, x));
	while (ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		i = 0;
		while (line[i])
			write(fd[1], line + i++, 1);
		write(fd[1], "\n", 1);
		free(line);
		write(1, "here_doc>", 9);
		x++;
		line = get_next_line(0);
		if (!line)
			return (warning_here_doc(lim, x));
	}
	free(line);
}

void	put_here_doc(t_dir **here, char *cmd)
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
			compt = create_here_list(here, cmd, i);
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

int	create_here_list(t_dir **here, char *cmd, int i)
{
	t_dir	*ptr;

	if (!*here)
	{
		*here = create_here_maillon(cmd, i);
		if (!*here || (*here)->fd == -1)
			return (1);
	}
	else
	{
		ptr = go_to_last(here);
		close(ptr->fd);
		ptr->next = create_here_maillon(cmd, i);
		if (!ptr->next || ptr->next->fd == -1)
			return (1);
	}
	return (0);
}

t_dir	*create_here_maillon(char *cmd, int i)
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
	tmp->fd = write_here_doc_on_fd(lim);
	free(lim);
	return (tmp);
}
