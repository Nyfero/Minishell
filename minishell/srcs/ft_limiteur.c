/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limiteur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:53:43 by gsap              #+#    #+#             */
/*   Updated: 2022/03/10 14:24:36 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*grep_indir(char const *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' && bool_not_in_quotes(&str[i]))
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
		return (error_limiteur(str[i]));
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	if (str[i] == '<' || str[i] == '>')
		return (error_limiteur(str[i]));
	while (str[i] && ((str[i] != ' ' && str[i] != '|' && str[i] != '<'
				&& str[i] != '>') || !bool_not_in_quotes(&str[i])))
		i++;
	lim = ft_substr(str, j, i - j);
	if (!lim)
		return (NULL);
	lim = del_quotes(lim);
	if (!lim)
		return (NULL);
	return (lim);
}

char	*error_limiteur(const char str)
{
	if (!str)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (str == '<')
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	else if (str == '>')
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	return (NULL);
}
