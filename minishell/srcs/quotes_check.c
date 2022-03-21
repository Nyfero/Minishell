/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:13:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 17:33:55 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoie 1 si l'élément n'est pas dans des quotes et 0 s'il y est.
*/

int	bool_not_in_quotes(char const *s)
{
	if (bool_not_in_simple(s) && bool_not_in_double(s))
		return (1);
	return (0);
}

int	bool_not_in_simple(char const *s)
{
	int	compt;
	int	i;

	compt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			compt++;
		i++;
	}
	if (compt % 2)
		return (0);
	return (1);
}

int	bool_not_in_double(char const *s)
{
	int	compt;
	int	i;

	compt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			compt++;
		i++;
	}
	if (compt % 2)
		return (0);
	return (1);
}

char	*get_words_in_quotes(char *str, char c)
{
	int		i;
	char	*res;

	i = 1;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 1;
	while (str[i] && str[i] != c)
	{
		res[i - 1] = str[i];
		i++;
	}
	res[i - 1] = 0;
	return (res);
}

int	ft_strchr_quotes(char const *s, char c)
{
	int	i;

	i = -1;
	if (s == 0)
		return (0);
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}
