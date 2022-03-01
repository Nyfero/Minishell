/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/01 18:16:15 by jgourlin         ###   ########.fr       */
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
	while (str[i] && (str[i] != ' ' || str[i] != '|' || str[i] != '<' || str[i] == '>'))
		i++;
	lim = ft_substr(str, j, i - j);
	if (!lim)
		return (NULL);
	return (lim);
}

int	read_here_doc(char *lim)
{
	int		fd;
	char	*line;		//free

	fd = open(".", O_TMPFILE | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("File cassé\n", 2);
		return (-1);
	}
	write(1, "here_doc>", 9);
	line = get_next_line(0);
	while (ft_strncmp(line, lim, ft_strlen(lim) + 1))
	{
		write(fd, &line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		write(1, "here_doc>", 9);
		line = get_next_line(0);
	}
	free(line);
	return (fd);
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


/*int	check_here_doc(char *dup, int i)
{
	int	j;

	j = i;
	while (dup[j] && dup[j] == '<')
		j++;
	return (j - i);
}*/
