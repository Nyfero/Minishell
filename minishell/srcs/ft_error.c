/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:48:46 by gsap              #+#    #+#             */
/*   Updated: 2022/03/05 17:27:39 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *err)
{
	ft_putstr_fd(err, 2);
	return (1);
}

void	print_error_wrpath(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("' ", fd);
	ft_putendl_fd(WR_PATH, fd);
}
