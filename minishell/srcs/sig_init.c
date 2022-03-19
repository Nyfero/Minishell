/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:15:59 by gsap              #+#    #+#             */
/*   Updated: 2022/03/19 19:25:10 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_main(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	if (sigemptyset(&sint.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	if (sigemptyset(&squit.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	sint.sa_handler = &sigint_main;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = &sigquit_main;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}

void	signal_pipex(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	if (sigemptyset(&sint.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	if (sigemptyset(&squit.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	sint.sa_handler = &sigint_pipex;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = &sigquit_pipex;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}


void	signal_here_doc(void)
{
	struct sigaction	sint;

	if (sigemptyset(&sint.sa_mask))
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	sint.sa_handler = &sigint_here_doc;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
}
