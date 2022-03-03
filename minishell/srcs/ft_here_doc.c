/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/03 15:04:26 by gsap             ###   ########.fr       */
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

void	put_here_doc(t_in **here, char *cmd)
{
	int		i;
	int		compt;
	t_in	*ptr;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '<')
		{
			compt = 0;
			while (cmd[i] == '<')
			{
				i++;
				compt++;
			}
			if (compt == 2)
			{
				if (!*here)
				{
					*here = create_here_maillon(cmd, i);
					if (!*here)
						return ;
				}
				else
				{
					ptr = go_to_last(here);
					ptr->next = create_here_maillon(cmd, i);
					if (!ptr->next)
						return ;
				}
			}
			else if (compt > 2)
			{
				ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				return ;
			}
		}
	}
}

t_in	*create_here_maillon(char *cmd, int i)
{
	char 	*lim;
	t_in	*tmp;

	tmp = ft_calloc(sizeof(t_in), 1);
	if (!tmp)
	{
		ft_putstr_fd("Error malloc t_in\n", 2);
		return (NULL);
	}
	tmp->pos = i - 2;
	lim = grep_indir(&cmd[i - 2]);
	printf("lim: %s\n", lim);
	tmp->fd = write_here_doc_on_fd(lim);
	free(lim);
	tmp->next = NULL;
	return (tmp);
}

/*
**	Une fontion qui me dis si j'ai affaire a un here doc ou a un infile
**	Renvoie 2 si here_doc, 1 si infile et 0 sinon
*/
int	check_in_or_here(char const *cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '<')
		{
			if (cmd[i + 1])
			{
				if (cmd[i + 1] == '<')
					ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				else
					return (2);
			}
			else
			{
				ft_putstr_fd("bash: syntax error near unexpected token\n",2);
				ft_putstr_fd("`newline'\n", 2);
			}
		}
		else
			return (1);
	}
	return (0);
}


/*
**	Une fonction qui me dis si j'ai en dernier un here doc ou un infile
**	Renvoie 2 si here_doc, 1 si infile et 0 sinon
*/

int	check_last_indir(char const *cmd)
{
	int		i;
	//char	*tmp;

	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '<' && not_in_quotes(&cmd[i]))
		{
			if ((i - 1) >= 0 && cmd[i - 1] == '<')
				return (2);
			/*else
			{
				tmp = get_limiteur(&cmd[i + 1]);
				if (ft_file_access(tmp) == 0 || ft_file_access(tmp) == -1)
				{
					free(tmp);
					return (0);
				}
				free(tmp);
			}*/
			return (1);
		}
		i--;
	}
	return (0);
}
