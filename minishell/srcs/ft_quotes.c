/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:13:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/17 17:51:21 by gsap             ###   ########.fr       */
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
	while(s[i])
	{
		if (s[i] == '\'')
			compt++;
		i++;
	}
	if ((compt % 2))
		return (0);
	return (1);
}

int	bool_not_in_double(char const *s)
{
	int	compt;
	int	i;

	compt = 0;
	i = 0;
	while(s[i])
	{
		if (s[i] == '\"')
			compt++;
		i++;
	}
	if ((compt % 2))
		return (0);
	return (1);
}

char	*del_simple(char *lim)
{
	char 	*before;
	char	*after;
	int		i;

	i = -1;
	while (lim[++i])
	{
		if (lim[i] == '\'' && bool_not_in_double(&lim[i]))
		{
			before = ft_substr(lim, 0, i);
			if (lim[i + 1])
			{
				after = ft_substr(lim, i + 1, ft_strlen(lim) - i);
				free(lim);
				lim = ft_strjoin_and_free_all(before, after);
			}
			else
			{
				free(lim);
				lim = ft_strdup(before);
				free(before);
			}
			if (!lim)
				return (NULL);
		}
	}
	if (!lim)
		return (NULL);
	return (lim);
}

char	*get_words_in_quotes(char *str, char c)
{
	int	i;
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

int ft_strchr_quotes(char const *s, char c)
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

char	*del_quotes(char *lim)
{
	char 	*before;
	char	*after;
	char	*tmp;
	int		i;

	i = 0;
	tmp = 0;
	while (lim[i])
	{
		if (((lim[i] == '\"' && bool_not_in_simple(&lim[i])) || (lim[i] == '\"'
			&& !bool_not_in_simple(&lim[i]) && !ft_strchr_quotes(tmp, '\"')))
				|| ((lim[i] == '\'' && bool_not_in_double(&lim[i]))
					|| (lim[i] == '\'' && !bool_not_in_double(&lim[i])
						&& !ft_strchr_quotes(tmp, '\''))))
		{
			if (tmp)
				free(tmp);
			tmp = get_words_in_quotes(lim + i, lim[i]);
			before = ft_substr(lim, 0, i);
			if (lim[i + 1])
			{
				after = ft_substr(lim, i + 1, ft_strlen(lim));
				free(lim);
				lim = ft_strjoin_and_free_all(before, after);
			}
			else
			{
				free(lim);
				lim = ft_strdup(before);
				free(before);
			}
			if (!lim)
				return (NULL);
		}
		else
			i++;
	}
	if (!lim)
		return (NULL);
	return (lim);
}
