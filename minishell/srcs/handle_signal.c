/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:29:38 by gsap              #+#    #+#             */
/*   Updated: 2022/03/17 16:05:15 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	sint.sa_handler = &handle_sigint;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = &handle_sigquit;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}

/*
**	ctr + c
**	ret 130
*/
void	handle_sigint(int sig)
{
	if (sig == 0)
		;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

/*
**	ctr + \
*/
void	handle_sigquit(int sig)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (sig == 0)
		;
}
