/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:29:38 by gsap              #+#    #+#             */
/*   Updated: 2022/02/24 17:49:12 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
*/
void	handle_sigint(int sig)
{
	if (sig == 0)
		;
	printf("\nPrompt> ");
}

/*
**	ctr + \
*/
void	handle_sigquit(int sig)
{
	if (sig == 0)
		;
}
