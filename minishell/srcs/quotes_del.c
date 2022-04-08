/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:47:12 by gsap              #+#    #+#             */
/*   Updated: 2022/04/08 11:11:02 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_simple(char *lim)
{
	char	*before;
	int		i;

	i = -1;
	while (lim[++i])
	{
		if (lim[i] == '\'' && bool_not_in_double(&lim[i]))
		{
			before = ft_substr(lim, 0, i);
			lim = replace_lim(lim, before, i);
			if (!lim)
				return (NULL);
		}
	}
	if (!lim)
		return (NULL);
	return (lim);
}

char	*replace_lim(char *lim, char *before, int i)
{
	char	*after;

	if (lim[i + 1])
	{
		after = ft_substr(lim, i + 1, ft_strlen(lim) - i);
		free(lim);
		lim = ft_strjoin_and_free_all(before, after);
	}
	else
	{
		free(lim);
		if (before)
		{
			lim = ft_strdup(before);
			free(before);
		}
		else
			return (NULL);
	}
	if (!lim)
		return (NULL);
	return (lim);
}

char	*del_quotes(char *lim)
{
	char	*before;
	char	*tmp;
	int		i;

	i = 0;
	tmp = 0;
	while (lim[i])
	{
		if (little_check(lim, i, tmp))
		{
			tmp = get_words_in_quotes(lim + i, lim[i]);
			before = ft_substr(lim, 0, i);
			lim = replace_lim(lim, before, i);
			if (!lim)
				return (NULL);
		}
		else
			i++;
	}
	if (tmp)
		free(tmp);
	if (!lim)
		return (NULL);
	return (lim);
}

int	little_check(char *lim, int i, char *tmp)
{
	if (((lim[i] == '\"' && bool_not_in_simple(&lim[i])) || (lim[i] == '\"'
				&& !bool_not_in_simple(&lim[i])
				&& !ft_strchr_quotes(tmp, '\"'))) || ((lim[i] == '\''
				&& bool_not_in_double(&lim[i])) || (lim[i] == '\''
				&& !bool_not_in_double(&lim[i])
				&& !ft_strchr_quotes(tmp, '\''))))
	{
		if (tmp)
			free(tmp);
		return (1);
	}
	return (0);
}

char	*del_quotes_first_arg(char *tmp, int i, char *before, char *after)
{
	while (tmp[i] && tmp[i] != ' ')
	{
		if (tmp [i] == '\"' || tmp[i] == '\'')
		{
			before = ft_substr(tmp, 0, i);
			after = ft_substr(tmp, i + 1, ft_strlen(tmp));
			free(tmp);
			if (!before && !after)
				return (NULL);
			tmp = ft_strdup("");
			if (before)
				tmp = ft_strjoin_and_free_all(before, tmp);
			if (!tmp)
				return (NULL);
			if (after)
				tmp = ft_strjoin_and_free_all(tmp, after);
			if (!tmp)
				return (NULL);
		}
		else
			i++;
	}
	return (tmp);
}
