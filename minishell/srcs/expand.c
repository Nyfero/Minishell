/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 21:44:47 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char const *inpt, t_env **env)
{
	char	**dup;
	char	*expand;
	int		i;

	dup = ft_split_minishell(inpt, ' ');
	i = -1;
	expand = NULL;
	while (dup[++i])
	{
		dup[i] = ft_expand_var(dup[i], env);
		if (!dup[i])
			return (NULL);
		if (i > 0)
		{
			expand = ft_strjoin_and_free_s1(expand, " ");
			expand = ft_strjoin_and_free_s1(expand, dup[i]);
		}
		else
			expand = ft_strdup(dup[i]);
	}
	if (dup)
		ft_free_ls(dup);
	return (expand);
}

char	*ft_expand_var(char *dup, t_env **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (dup[i])
	{
		if (dup[i] == '$')
		{
			if (bool_not_in_quotes(&dup[i]))
				tmp = expand_no_quotes(dup, env);
			else
				tmp = expand_with_quotes(dup, env);
			if (!tmp)
				return (NULL);
			return (tmp);
		}
		else
			i++;
	}
	return (dup);
}

char	*expand_no_quotes(char *dup, t_env **env)
{
	t_env	*ptr;
	int		j;
	int		i;

	i = 0;
	while (dup[i])
	{
		ptr = NULL;
		if (dup[i] == '$')
		{
			ptr = check_good_expand(&dup[i], env);
			if (!ptr || ptr->flags % 2 || !ptr->var)
				j = i - 1;
			else
				j = i + ft_strlen(ptr->name);
			dup = replace_expand(dup, i, env);
			i = j;
		}
		if (!ptr || ptr->flags % 2 || !ptr->var)
			i++;
	}
	return (dup);
}

char	*expand_with_quotes(char *dup, t_env **env)
{
	t_env	*ptr;
	int		i;
	int		j;

	if (dup[0] == '\'')
		return (dup);
	i = 0;
	while (dup[i])
	{
		ptr = NULL;
		if (dup[i] == '$')
		{
			ptr = check_good_expand(&dup[i], env);
			if (!ptr || ptr->flags % 2 || !ptr->var)
				j = i - 1;
			else
				j = i + ft_strlen(ptr->name);
			dup = replace_expand(dup, i, env);
			i = j;
		}
		if (!ptr || ptr->flags % 2 || !ptr->var)
			i++;
	}
	return (dup);
}

char	*replace_expand(char *dup, int i, t_env **env)
{
	char	*before;
	char	*after;
	t_env	*ptr;
	int		j;

	before = ft_substr(dup, 0, i);
	if (dup[i + 1] && dup[i + 1] == '$')
		return (replace_dolls(dup, before, i));
	ptr = check_good_expand(&dup[i], env);
	if (!ptr)
		j = i + len_name(&dup[i]);
	else
		j = i + 1 + ft_strlen(ptr->name);
	after = ft_substr(dup, j, ft_strlen(dup));
	if (!after)
		after = ft_strdup("");
	free(dup);
	if (!ptr || ptr->flags % 2 || !ptr->var)
		dup = ft_strjoin_and_free_all(before, after);
	else
	{
		dup = ft_strjoin_and_free_s1(before, ptr->var);
		dup = ft_strjoin_and_free_all(dup, after);
	}
	return (dup);
}
