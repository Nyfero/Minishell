/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:53:48 by gsap              #+#    #+#             */
/*   Updated: 2022/01/26 17:46:08 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(int flag, char *str)
{
	ft_putstr_fd(str, 1);
	if (flag == FALSE)
		ft_putchar_fd('\n', 1);
	return ;
}
