/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:20:03 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 19:07:50 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **str, t_env **env)
{
	t_env	*ptr;
	int		i;

	if (ft_lstrlen(str) > 1 )
	{
		i = 1;
		while (str[i])
		{
			if (ft_strncmp(str[i], "env", 4) == 0)
				i++;
			else
			{
				printf("env: '%s' %s\n", str[i], WR_PATH);
				return (1);
			}
		}
	}
	ptr = *env;
	i = 0;
	printf("addresse de env %p\n", *env);
	while (ptr)
	{
		if (ptr->flags == 0)
		{
			printf("%d=>%s%s\n", i, ptr->name, ptr->var);
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}
