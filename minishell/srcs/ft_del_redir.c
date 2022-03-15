/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:47:33 by gsap              #+#    #+#             */
/*   Updated: 2022/03/15 10:11:54 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_redir(char *expand)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = remove_infile(expand, i);
	tmp = remove_out(tmp, i);
	return (tmp);
}

char	*remove_infile(char *expand, int i)
{
	char	*tmp;
	int		compt;

	tmp = NULL;
	i = -1;
	while (expand[++i])
	{
		compt = 0;
		while (expand[i] == '<' && bool_not_in_quotes(&expand[i]))
		{
			i++;
			compt++;
		}
		if (compt)
		{
			if (compt == 1)
				compt = i - 1;
			else
				compt = i - 2;
			tmp = blank_replace(tmp, expand, i , compt);
		}
	}
	if (!tmp)
		return (expand);
	return (tmp);
}

char	*remove_out(char *expand, int i)
{
	char	*tmp;
	int		compt;

	tmp = NULL;
	i = -1;
	while (expand[++i])
	{
		compt = 0;
		while (expand[i] == '>' && bool_not_in_quotes(&expand[i]))
		{
			i++;
			compt++;
		}
		if (compt)
		{
			if (compt == 1)
				compt = i - 1;
			else
				compt = i - 2;
			tmp = blank_replace(tmp ,expand, i, compt);
		}
	}
	if (!tmp)
		return (expand);
	return (tmp);
}

char	*blank_replace(char *tmp, char *expand, int i, int compt)
{
	char	*after;

	if (!tmp)
		tmp = ft_substr(expand, 0, compt);
	else
		tmp = ft_substr(tmp, 0, compt);
	while (expand[i] == '>')
		i++;
	while (expand[i] == ' ')
		i++;
	while (expand[i] && ((expand[i] != ' ' && expand[i] != '|'
			&& expand[i] != '<' && expand[i] != '>')
				|| !bool_not_in_quotes(&expand[i])))
		i++;
	after = ft_strdup(" ");
	while (compt++ < i)
		after = ft_strjoin_and_free_s1(after, " ");
	tmp = ft_strjoin_and_free_all(tmp, after);
	after = ft_substr(expand, i, ft_strlen(expand) - i);
	if (after)
		tmp = ft_strjoin_and_free_all(tmp, after);
	return (tmp);
}
