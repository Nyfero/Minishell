/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/10 17:22:14 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char const *inpt, t_env **env)
{
	char	**dup;
	char	*expand;
	int		i;
	int		j;

	if (!*env)
		return ((char *)inpt);
	dup = ft_split(inpt, ' ');
	i = -1;
	expand = NULL;
	while (dup[++i])
	{
		dup[i] = del_double(dup[i]);
		j = -1;
		while (dup[i][++j])
			dup[i] = ft_expand_utils(dup[i], j, env);
		if (i > 0)
		{
			expand = ft_strjoin_and_free_s1(expand, " ");
			expand = ft_strjoin_and_free_all(expand, dup[i]);
		}
		else
			expand = ft_strdup(dup[i]);
	}
	expand = del_quotes(expand);
	return (expand);
}

char	*ft_expand_utils(char *dup, int j, t_env **env)
{
	char	*tmp;
	t_env	*ptr;

	if (dup[j] == '$' && bool_not_in_simple(&dup[j]))
	{
		if (dup[j + 1] && dup[j + 1] != '<' && dup[j + 1] != '>')
		{
			ptr = ft_get_var(&dup[j + 1], *env);
			if (ptr)
			{
				tmp = ft_substr(dup, 0, j);
				free(dup);
				tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
			}
			else
			{
				tmp = ft_substr(dup, 0, j);
				free(dup);
			}
			return (tmp);
		}
	}
	return (dup);
}
