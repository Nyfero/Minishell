/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:15:19 by gsap              #+#    #+#             */
/*   Updated: 2021/05/28 10:25:29 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_is_sep(char c, char const *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	compt_deb(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_is_sep(s1[i], set))
		i++;
	return (i);
}

size_t	compt_fin(char const *s1, char const *set)
{
	size_t	x;
	size_t	i;

	x = 0;
	i = 0;
	while (s1[i])
		i++;
	if (i > 1)
	{
		i--;
		while (ft_is_sep(s1[i], set))
		{
			x++;
			i--;
		}
	}
	return (x);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	x;

	if (!s1)
		return (NULL);
	if (!set)
		str = ft_strdup(s1);
	else
	{
		i = compt_deb(s1, set);
		x = compt_fin(s1, set);
		if ((i - x) < ft_strlen(s1))
			str = ft_substr(s1, i, ft_strlen(s1) - (i + x));
		else
			return (NULL);
	}
	return (str);
}
