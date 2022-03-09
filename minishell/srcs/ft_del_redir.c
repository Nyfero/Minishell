/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:47:33 by gsap              #+#    #+#             */
/*   Updated: 2022/03/09 13:20:30 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_redir(char *expand)
{
	char	*tmp;

	tmp = remove_here(expand);
	tmp = remove_infile(tmp);
	tmp = remove_out(tmp);
	printf("tmp:%s\n", tmp);
	return (tmp);
}

char	*remove_here(char *expand)
{
	char	*tmp;
	char	*after;
	int		compt;
	int		i;

	tmp = NULL;
	i = -1;
	while (expand[++i])
	{
		compt = 0;
		while (expand[i] == '<' && bool_not_in_simple(&expand[i]))
		{
			i++;
			compt++;
		}
		if (compt == 2)
		{
			compt = i - 2;
			if (!tmp)
				tmp = ft_substr(expand, 0, compt);
			else
				tmp = ft_substr(tmp, 0, compt);
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
		}
	}
	if (!tmp)
		return (expand);
	return (tmp);
}

char	*remove_infile(char *expand)
{
	char	*tmp;
	char	*after;
	int		compt;
	int		i;

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
		if (compt == 1)
		{
			compt = i - 1;
			if (!tmp)
				tmp = ft_substr(expand, 0, compt);
			else
				tmp = ft_substr(tmp, 0, compt);
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
		}
	}
	if (!tmp)
		return (expand);
	return (tmp);
}

char	*remove_out(char *expand)
{
	char	*tmp;
	char	*after;
	int		compt;
	int		i;

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
		}
	}
	if (!tmp)
		return (expand);
	return (tmp);
}
