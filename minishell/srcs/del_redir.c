/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:47:33 by gsap              #+#    #+#             */
/*   Updated: 2022/03/26 18:11:26 by gsap             ###   ########.fr       */
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
			compt = return_compt(compt, i);
			tmp = blank_replace(tmp, expand, i, compt);
		}
	}
	if (!tmp)
		return (expand);
	free(expand);
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
			compt = return_compt(compt, i);
			tmp = blank_replace(tmp, expand, i, compt);
		}
	}
	if (!tmp)
		return (expand);
	free(expand);
	return (tmp);
}

char	*blank_replace(char *tmp, char *s, int i, int compt)
{
	char	*after;

	if (!tmp)
		tmp = ft_substr(s, 0, compt);
	else
	{
		after = tmp;
		tmp = ft_substr(after, 0, compt);
		free(after);
	}
	while (s[i] == '>')
		i++;
	while (s[i] == ' ')
		i++;
	while (s[i] && ((s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>')
			|| !bool_not_in_quotes(&s[i])))
		i++;
	after = ft_strdup(" ");
	while (compt++ < i)
		after = ft_strjoin_and_free_s1(after, " ");
	tmp = ft_strjoin_and_free_all(tmp, after);
	after = ft_substr(s, i, ft_strlen(s));
	if (after)
		tmp = ft_strjoin_and_free_all(tmp, after);
	return (tmp);
}

int	return_compt(int compt, int i)
{
	if (compt == 1)
		compt = i - 1;
	else
		compt = i - 2;
	return (compt);
}
