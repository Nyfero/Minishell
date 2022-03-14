/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/14 11:44:10 by gsap             ###   ########.fr       */
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
	printf("expand = %s\n", expand);
	return (expand);
}

/*
**	2 Cas: soit $ est dans des quotes soit il ne l'est pas. S'il ne l'est pas i
**	est bon sinon je dois retirer de i les quotes.
*/

char	*ft_expand_var(char *dup, t_env **env)
{
	char	*tmp;
	t_env	*ptr;
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
			free(dup);
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
		free(dup);
		tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = ft_substr(dup, 0, i);
		if (!tmp)
			return (NULL);
		free(dup);
	}
	return (tmp);
}

t_env	*check_good_expand(char *str, int i, t_env **env)
{
	char	*tmp;
	t_env	*ptr;
	int		j;

	if (str[i + 1])
		tmp = ft_strdup(&str[i + 1]);
	else
		return (NULL);
	if (!tmp)
		return (NULL);
	ptr = ft_get_var(str, *env);
	free(tmp);
	return (ptr);
}
if (dup[j + 1] && dup[j + 1] != '<' && dup[j + 1] != '>')
{
	ptr = ft_get_var(&dup[j + 1], *env);
