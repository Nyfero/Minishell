/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:30:08 by gsap              #+#    #+#             */
/*   Updated: 2022/02/02 11:46:14 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getenv(t_env **env, char **envp)
{
	int	i;
	int	len_envp;

	if (!env)
	{
		printf("NO ENV\n");
		return (NULL);
	}
	i = 0;

	*env = create_env_list(envp);
}
