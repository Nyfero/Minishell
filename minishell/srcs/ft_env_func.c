/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:30:08 by gsap              #+#    #+#             */
/*   Updated: 2022/02/02 17:47:09 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static t_env	*ft_test(t_env *env)
{
	printf("%s%s\n", env->name, env->var);
	return (env->next);
}*/

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

/*
**	A mettre au propre et faire les unset et export
*/

void	create_env_list(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*ptr;
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
	j = i;
	while (str[j])
		j++;
	tmp->name = ft_substr(str, 0, i + 1);
	tmp->var = ft_substr(str, i + 1, j);
	tmp->flags = 0;
	tmp->next = NULL;
	if (!*env)
		*env = tmp;
	else
	{
		ptr = *env;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = tmp;
	}
	return ;
}
