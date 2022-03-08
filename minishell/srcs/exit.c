/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:14:04 by gsap              #+#    #+#             */
/*   Updated: 2022/03/08 16:11:43 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **tmp)
{
	int	i;

	if (tmp[2])
	{
		ft_putendl_fd("exit : too many arguments", 2);
		return (1);
	}
	if (!tmp[1])
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else
	{
		i = -1;
		while (tmp[1][++i])
		{
			if (!ft_isdigit(tmp[1][i]))
			{
				ft_putstr_fd("exit : ", 2);
				ft_putstr_fd(tmp[1], 2);
				ft_putendl_fd(": numeric arguments required", 2);
				exit(2);
			}
		}
		ft_putendl_fd("exit", 1);
		i = ft_atoi(tmp[1]);
		if (i > 256)
			i = i % 256;
		exit(i);
	}
	return (0);
}
