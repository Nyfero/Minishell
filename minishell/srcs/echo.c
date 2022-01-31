/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:53:48 by gsap              #+#    #+#             */
/*   Updated: 2022/01/27 14:23:02 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str)
{
	ft_putendl_fd(str, 1);
	return ;
}

void	ft_echo_n(char *str)
{
	ft_putstr_fd(str, 1);
	return ;
}
