/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/04 15:00:07 by gsap             ###   ########.fr       */
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
	dup = ft_split_minishell(inpt, ' ');
	i = -1;
	expand = NULL;
	while (dup[++i])
	{
		j = -1;
		while (++j < 3)
			dup[i] = ft_expand_utils(dup[i], j, env);
		if (i > 0)
		{
			expand = ft_strjoin_and_free_s1(expand, " ");
			expand = ft_strjoin_and_free_all(expand, dup[i]);
		}
		else
			expand = ft_strdup(dup[i]);
	}
	return (expand);
}

char	*ft_expand_utils(char *dup, int j, t_env **env)
{
	char	*tmp;
	t_env	*ptr;

	if (dup[j] == '$')
	{
		if (dup[j + 1] && dup[1] != '<' && dup[j + 1] != '$')
		{
			ptr = ft_get_var(&dup[j + 1], *env);
			if (ptr)
			{
				tmp = ft_substr(dup, 0, j);
				tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
				free(dup);
				dup = tmp;
			}
			else
			{
				tmp = ft_substr(dup, 0, j);
				free(dup);
				dup = tmp;
			}
		}
	}
	return (dup);
}
