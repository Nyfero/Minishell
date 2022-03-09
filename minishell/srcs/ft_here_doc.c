/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/09 13:18:53 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ouvre un pipe et écrit le here doc dedans puis renvoie fd[0]
*/

int	write_here_doc_on_fd(char *lim)
{
	int		fd[2];
	char	*line;
	int		i;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	write(1, "here_doc>", 9);
	line = get_next_line(0);
	while (ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		i = 0;
		while (line[i])
			write(fd[1], line + i++, 1);
		write(fd[1], "\n", 1);
		free(line);
		write(1, "here_doc>", 9);
		line = get_next_line(0);
	}
	close(fd[1]);
	free(line);
	return (fd[0]);
}

void	put_here_doc(t_dir **here, char *cmd)
{
	int		i;
	int		compt;

	i = -1;
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '<')
		{
			i++;
			compt++;
		}
		if (compt == 2 && bool_not_in_quotes(&cmd[i]))
		{
			compt = create_here_list(here, cmd, i);
			if (compt)
				return ;
		}
		else if (compt > 2 && bool_not_in_quotes(&cmd[i]))
		{
			ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
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
		if (!*here)
			return (1);
	}
	else
	{
		ptr = go_to_last(here);
		close(ptr->fd);
		ptr->next = create_here_maillon(cmd, i);
		if (!ptr->next)
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
	tmp->pos = i - 2;
	lim = grep_indir(&cmd[i - 2]);
	if (!lim)
		return (NULL);
	tmp->len_lim = ft_strlen(lim);
	tmp->fd = write_here_doc_on_fd(lim);
	free(lim);
	tmp->next = NULL;
	return (tmp);
}

/*
**	Une fonction qui me dis si j'ai en dernier un here doc ou un infile
**	Renvoie 2 si here_doc, 1 si infile et 0 sinon
*/

int	check_last_indir(char const *cmd)
{
	int		i;

	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '<' && bool_not_in_quotes(&cmd[i]))
		{
			if ((i - 1) >= 0 && cmd[i - 1] == '<')
				return (2);
			return (1);
		}
		i--;
	}
	return (0);
}
