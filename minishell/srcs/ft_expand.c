/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/15 12:00:43 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char const *inpt, t_env **env)
{
	char	**dup;
	char	*expand;
	int		i;

	if (!*env)
		return ((char *)inpt);
	dup = ft_split_minishell(inpt, ' ');
	i = -1;
	expand = NULL;
	while (dup[++i])
	{
		dup[i] = ft_expand_var(dup[i], env);
		if (i > 0)
		{
			expand = ft_strjoin_and_free_s1(expand, " ");
			expand = ft_strjoin_and_free_all(expand, dup[i]);
		}
		else
			expand = ft_strdup(dup[i]);
	}
	free(dup);
	return (expand);
}

/*
**	2 Cas: soit $ est dans des quotes soit il ne l'est pas. S'il ne l'est pas i
**	est bon sinon je dois retirer de i les quotes.
*/

char	*ft_expand_var(char *dup, t_env **env)
{
	char	*tmp;
	int		i;

	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '$')
		{
			if (bool_not_in_quotes(&dup[i]))
				tmp = expand_no_quotes(dup, i, env);
			else
				tmp = expand_with_quotes(dup, i, env);
			return (tmp);
		}
	}
	return (dup);
}

char	*expand_no_quotes(char *dup, int i, t_env **env)
{
	t_env	*ptr;
	char	*tmp;

	ptr = check_good_expand(dup, i, env);
	if (ptr)
	{
		tmp = ft_substr(dup, 0, i);
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = ft_substr(dup, 0, i);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

char	*expand_with_quotes(char *dup, int i, t_env **env)
{
	t_env	*ptr;
	char	*tmp;

	tmp = del_double(dup);
	printf("tmp = %s\n", tmp);
	if (!bool_not_in_simple(&tmp[i]))
		return (del_quotes(tmp));
	tmp = del_quotes(tmp);
	ptr = check_good_expand(tmp, i, env);
	if (ptr)
	{
		tmp = ft_substr(dup, 0, i);
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = ft_substr(dup, 0, i);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

t_env	*check_good_expand(char *str, int i, t_env **env)
{
	char	*tmp;
	t_env	*ptr;

	if (str[i + 1])
		tmp = ft_strdup(&str[i + 1]);
	else
		return (NULL);
	if (!tmp)
		return (NULL);
	if (tmp[i] == '<' || tmp[i] == '>')
	{
		free(tmp);
		return (NULL);
	}
	ptr = ft_get_var(tmp, *env);
	free(tmp);
	return (ptr);
}
