/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:48:46 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 16:41:27 by gsap             ###   ########.fr       */
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

int	print_error_syntax(int x)
{
	char	*err;

	if (x == 0)
		err = "syntax error near unexpected token `<'";
	else
		err = "syntax error near unexpected token `>'";
	ft_putendl_fd(err, 2);
	return (-2);
}

void	warning_here_doc(char *s, int x)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("')", 2);
}
