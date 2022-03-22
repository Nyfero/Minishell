/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:29:38 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 19:15:30 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

/*
**	sigint
**	ctr + c
**	ret 130
*/
void	sigint_main(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_sig = 130;
}

void	sigint_child(int sig)
{
	(void)sig;
	g_sig = 130;
}

/*
**	sigquit
**	ctr + \
**	ret 131
*/

void	sigquit_main(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	sigquit_child(int sig)
{
	(void)sig;
	g_sig = 131;
}
