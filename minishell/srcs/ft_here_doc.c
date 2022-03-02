/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/02 18:05:24 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_here_doc(char const *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' && not_in_quotes(&str[i]))
		{
			j = i;
			while (str[i] == '<')
				i++;
			if (i - j > 2)
			{
				ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				return (NULL);
			}
			return (get_limiteur(&str[i]));
		}
	}
	return (NULL);
}

char	*get_limiteur(const char *str)
{
	char	*lim;
	int		i;
	int		j;

	i = 0;
	if (!str[i])
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (NULL);
	}
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '<')
			ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		else
			ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (NULL);
	}
	while (str[i] && ((str[i] != ' ' && str[i] != '|' && str[i] != '<'
		&& str[i] != '>') || !not_in_quotes(&str[i])))
		i++;
	lim = ft_substr(str, j, i - j);
	if (!lim)
		return (NULL);
	return (lim);
}

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
					ptr = *here;
					while (ptr->next != NULL)
						ptr = ptr->next;
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
	lim = handle_here_doc(&cmd[i - 2]);
	printf("lim: %s\n", lim);
	tmp->fd = write_here_doc_on_fd(lim);
	free(lim);
	return (tmp);
}

void	put_infile(t_in **infile, char *cmd, t_env **env)
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
			if (compt == 1)
			{
				if (!*infile)
				{
					*infile = create_infile_maillon(cmd, i, env);
					if (!*infile)
						return ;
				}
				else
				{
					ptr = *infile;
					while (ptr->next != NULL)
						ptr = ptr->next;
					ptr->next = create_infile_maillon(cmd, i, env);
					if (!ptr->next)
						return ;
				}
			}
		}
	}
}

t_in	*create_infile_maillon(char *cmd, int i, t_env **env)
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
	lim = ft_expand(handle_here_doc(&cmd[i - 2]), env);
	if (ft_file_access(lim) == 0)
	{
		ft_putstr_fd(lim, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(lim);
		return (NULL);
	}
	if (ft_file_access(lim) == -1) //check si j'ai les droits sur le dossier
	{
		ft_putstr_fd(lim, 2);
		if (access(lim, F_OK | R_OK))
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": is a directory\n", 2);
		free(lim);
		return (NULL);
	}
	tmp->fd = open(lim, O_RDONLY);
	if (tmp->fd == -1)
	{
		perror("open");
		free(lim);
		return (NULL);
	}
	free(lim);
	return (tmp);
}

/*char	*replace_here_doc(char *dup, int i)
{
	char	*lim;		//free dans read_here_doc
	char	*before;	//free dans le join
	char	*here;		//free dans le join
	char	*after;		//free dans le join
	int		len_lim;

	lim = get_limiteur(&dup[i]);
	if (!lim)
		return (NULL);
	len_lim = ft_strlen(lim) + 2;
	before = ft_substr(dup, 0, i);
	here = read_here_doc(lim);
	after = ft_strdup(&dup[i + len_lim]);
	printf("before:%s\nhere:%s\nafter:%s\n",before, here, after);
	if (!here)
	{
		if (!before && !after)
			return (NULL);
		else
			dup = ft_strjoin_and_free_all(before, after);
	}
	else
	{
		dup = ft_strjoin_and_free_all(before, here);
		if (after[0])
			dup = ft_strjoin_and_free_all(dup, after);
	}
	return (dup);
}
*/

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
					//`newline'\n", 2);
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
	int	i;

	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '<')
		{
			if ((i - 1) >= 0 && cmd[i - 1] == '<')
				return (2);
			return (1);
		}
		i--;
	}
	return (0);
}
