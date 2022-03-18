/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/18 19:07:27 by gsap             ###   ########.fr       */
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
	int		len;

	i = 0;
	len = (int)ft_strlen(dup) - 1;
	while (i < len)
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
	char	*tmp;

	ptr = check_good_expand(&dup[get_dolls(dup)], env);
	if (ptr && ptr->flags % 2 == 0)
	{
		tmp = ft_substr(dup, 0, get_dolls(dup));
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = ft_substr(dup, 0, get_dolls(dup));
		if (!tmp)
			return (NULL);
	}
	return (tmp);
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
		if (dup[i] == '$')
		{
			ptr = check_good_expand(&dup[i], env);
			if (!ptr)
				j = i;
			else
				j = i + 1 + ft_strlen(ptr->name);
			dup = replace_expand(dup, i, env);
			i = j;
		}
		if (i < (int)ft_strlen(dup))
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
	ptr = check_good_expand(&dup[i], env);
	if (!ptr)
		j = i;
	else
		j = i + 1 + ft_strlen(ptr->name);
	after = ft_substr(dup, j, ft_strlen(dup));
	free(dup);
	if (!ptr || ptr->flags % 2)
		dup = ft_strjoin_and_free_all(before, after);
	else
	{
		dup = ft_strjoin_and_free_s1(before, ptr->var);
		dup = ft_strjoin_and_free_all(dup, after);
	}
	return (dup);
}
