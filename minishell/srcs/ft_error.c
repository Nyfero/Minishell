/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:48:46 by gsap              #+#    #+#             */
/*   Updated: 2022/03/05 18:17:32 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *err)
{
	ft_putstr_fd(err, 2);
	return (1);
}

void	print_error_wrpath(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("' ", 2);
	ft_putendl_fd(WR_PATH, 2);
}

void	print_error_idf(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("' ", 2);
	ft_putendl_fd(WR_IDF, 2);
}
