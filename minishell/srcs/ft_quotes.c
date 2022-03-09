/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:13:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/09 13:13:23 by gsap             ###   ########.fr       */
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
	i = -1;
	while(s[++i])
		if (s[i] == '\'')
			compt++;
	if ((compt % 2))
		return (0);
	return (1);
}

int	bool_not_in_double(char const *s)
{
	int	compt;
	int	i;

	compt = 0;
	i = -1;
	while(s[++i])
		if (s[i] == '\"')
			compt++;
	if ((compt % 2))
		return (0);
	return (1);
}
