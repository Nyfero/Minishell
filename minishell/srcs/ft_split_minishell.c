/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:19:34 by gsap              #+#    #+#             */
/*   Updated: 2022/03/18 17:32:56 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_alloc_tmp(char const *s, char c)
{
	int		compt;
	int		i;
	char	**tmp;

	i = 0;
	compt = 0;
	if (ft_strlen(s))
		compt++;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && bool_not_in_quotes(&s[i]))
			if (s[i + 1])
				compt++;
		while (s[i] && s[i] != c)
			i++;
	}
	if (compt == 0)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), compt + 1);
	if (!tmp)
		return (NULL);
	tmp[compt] = 0;
	return (tmp);
}

static void	*ft_free_split(char **split, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
	return (NULL);
}

static char	*ft_assign_tmp(char const *s, char *tmp, size_t i)
{
	tmp[i] = 0;
	s--;
	while (i > 0)
		tmp[--i] = *s--;
	return (tmp);
}

static char	**ft_split_tmp(char const *s, char c, char **split)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*s)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		while (*s && (*s != c || !bool_not_in_quotes(s)))
		{
			i++;
			s++;
		}
		if (i > 0)
		{
			split[j] = ft_calloc(sizeof(char), i + 1);
			if (!split[j])
				return (ft_free_split(split, j));
			split[j] = ft_assign_tmp(s, split[j], i);
			j++;
		}
	}
	return (split);
}

char	**ft_split_minishell(char const *s, char c)
{
	char	**tmp;

	if (!s)
		return (NULL);
	tmp = ft_alloc_tmp(s, c);
	if (!tmp)
		return (NULL);
	tmp = ft_split_tmp(s, c, tmp);
	if (!tmp)
		return (NULL);
	return (tmp);
}
