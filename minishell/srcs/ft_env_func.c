/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:30:08 by gsap              #+#    #+#             */
/*   Updated: 2022/02/08 15:17:31 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **env, char **envp)
{
	int		i;
	t_env	*ptr;

	i = -1;
	while (envp[++i])
	{
		if (!*env)
			*env = create_env_maillon(envp[i], 0);
		else
		{
			ptr = *env;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = create_env_maillon(envp[i], 0);
		}
	}
}

t_env	*create_env_maillon(char *str, int flags)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = ft_calloc(sizeof(t_env), 1);
	if (!tmp)
	{
		printf("MALLOC FAILED\n");
		exit(1);
	}
	i = 0;
	while (str[i] != '=')
		i++;
	j = i + 1;
	while (str[j])
		j++;
	tmp->name = ft_substr(str, 0, i);
	tmp->var = ft_substr(str, i + 1, j);
	tmp->flags = flags;
	tmp->next = NULL;
	return (tmp);
}

t_env	*mod_env_maillon(char *str, t_env *ptr, int flags)
{
	int	i;

	if (ptr->var)
		free(ptr->var);
	ptr->var = NULL;
	ptr->flags = flags;
	i = 0;
	while (str[i] != '=')
		i++;
	ptr->var = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	return (ptr);
}
