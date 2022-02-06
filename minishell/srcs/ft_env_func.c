/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:30:08 by gsap              #+#    #+#             */
/*   Updated: 2022/02/04 10:54:06 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **env, char **envp)
{
	int		i;

	if (!envp)
	{
		printf("NO ENV\n");
		return ;
	}
	i = 0;
	while (envp[i])
	{
		create_env_list(env, envp[i]);
		i++;
	}
}

void	create_env_list(t_env **env, char *str)
{
	t_env	*ptr;

	if (!*env)
		*env = create_env_maillon(str, 0);
	else
	{
		ptr = *env;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = create_env_maillon(str, 0);
	}
	return ;
}

t_env	*create_env_maillon(char *str, int flags)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(t_env));
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
