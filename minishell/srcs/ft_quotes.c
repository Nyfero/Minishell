/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:13:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/15 16:42:57 by gsap             ###   ########.fr       */
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
	int	d_quotes;
	int	i;

	compt = 0;
	i = 0;
	d_quotes = 0;
	while(s[i])
	{
		if (s[i] == '\"')
			d_quotes++;
		if (s[i] == '\'' && d_quotes % 2 == 0)
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
	int	s_quotes;
	int	i;

	compt = 0;
	i = 0;
	s_quotes = 0;
	while(s[i])
	{
		if (s[i] == '\'')
			s_quotes++;
		if (s[i] == '\"' && s_quotes % 2 == 0)
			compt++;
		i++;
	}
	if ((compt % 2))
		return (0);
	return (1);
}

char	*del_simple(char *lim)
{
	char 	*tmp;
	char	*after;
	int		i;

	i = -1;
	while (lim[++i])
	{
		if (lim[i] == '\'' && bool_not_in_double(&lim[i]))
		{
			tmp = ft_substr(lim, 0, i);
			if (lim[i + 1])
			{
				after = ft_substr(lim, i + 1, ft_strlen(lim) - i);
				free(lim);
				lim = ft_strjoin_and_free_all(tmp, after);
			}
			else
			{
				free(lim);
				lim = ft_strdup(tmp);
				free(tmp);
			}
			if (!lim)
				return (NULL);
		}
	}
	if (!lim)
		return (NULL);
	return (lim);
}

char	*del_quotes(char *lim)
{
	char 	*tmp;
	char	*after;
	int		i;

	i = 0;
	while (lim[i])
	{
		if ((lim[i] == '\"' && bool_not_in_simple(&lim[i]))
			|| (lim[i] == '\'' && bool_not_in_double(&lim[i])))
		{
			tmp = ft_substr(lim, 0, i);
			if (lim[i + 1])
			{
				after = ft_substr(lim, i + 1, ft_strlen(lim) - i);
				free(lim);
				lim = ft_strjoin_and_free_all(tmp, after);
			}
			else
			{
				free(lim);
				lim = ft_strdup(tmp);
				free(tmp);
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
