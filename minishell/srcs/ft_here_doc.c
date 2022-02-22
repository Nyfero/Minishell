/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/02/22 17:05:33 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// boucle sur str et remplace mes _here_doc
char	*handle_here_doc(char const *str)
{
	char	*dup;
	//char	*tmp;
	int		i;
	int		bis;

	dup = ft_strdup(str);
	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '<' && not_in_quotes(&dup[i]))
		{
			bis = check_here_doc(dup, i);
			if (bis == 2)
			{
				dup = ft_strjoin_and_free_s1(ft_substr(dup, 0, i + 1 + ft_strlen(get_limiteur(&dup[i]) + 2)), read_here_doc(dup, i));
				//je join tout ce que j'ai chope a mon dup puis je join tout apres le _here_doc
				printf("dup:%s", dup);
				//gerer le _here_doc
			}
			i += bis;
		}
	}
	return (dup);
}

char	*read_here_doc(char *str, int i)
{
	char	*tmp;
	char	*bis;
	char 	*line;

	bis = ft_strdup("");
	tmp = get_limiteur(&str[i]);
	line = get_next_line(0);
	while (ft_strncmp(line, tmp, ft_strlen(tmp) + 1))
	{
		bis = ft_strjoin_and_free_s1(bis, line);
		bis = ft_strjoin_and_free_s1(bis, "\n");
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(tmp);
	return (bis);
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
