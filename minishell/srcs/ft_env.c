/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:20:03 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 10:18:56 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ptr->flags == 0)
			printf("%s%s\n", ptr->name, ptr->var);
		ptr = ptr->next;
	}
	return ;
}
