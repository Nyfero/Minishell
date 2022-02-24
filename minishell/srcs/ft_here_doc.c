/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/02/23 16:31:30 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_here_doc(char const *str)
{
	char	*dup; // pas besoin d'etre free ici
	int		i;
	int		ret;

	dup = ft_strdup(str);
	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '<' && not_in_quotes(&dup[i]))
		{
			ret = check_here_doc(dup, i);
			if (ret == 2)
			{
				ret = ft_strlen(dup);
				dup = replace_here_doc(dup, i);
				if (!dup)
					return (NULL);
				ret = ft_strlen(dup) - ret;
			}
			i += ret;
		}
	}
	return (dup);
}

char	*replace_here_doc(char *dup, int i)
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

char	*read_here_doc(char *lim)
{
	char	*ret;		//free si pas de here doc
	char	*line;		//free

	ret = ft_strdup("");
	write(1, "here_doc>", 9);
	line = get_next_line(0);
	if (ft_strncmp(line, lim, ft_strlen(lim) + 1) == 0)
	{
		free(ret);
		ret = NULL;
	}
	else
	{
		while (ft_strncmp(line, lim, ft_strlen(lim) + 1))
		{
			ret = ft_strjoin_and_free_s1(ret, line);
			free(line);
			ret = ft_strjoin_and_free_s1(ret, "\n");
			write(1, "here_doc>", 9);
			line = get_next_line(0);
		}
	}
	free(line);
	free(lim);
	return (ret);
}

char	*get_limiteur(const char *str)
{
	char	*lim;
	int		i;
	int		j;

	if (str[2] && str[2] == ' ')
		j = 3;
	else
		j = 2;
	i = j;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '$'))
		i++;
	if (str[i] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (NULL);
	}
	lim = ft_substr(str, j, i - j);
	return (lim);
}

int	check_here_doc(char *dup, int i)
{
	int	j;

	j = i;
	while (dup[j] && dup[j] == '<')
		j++;
	return (j - i);
}
