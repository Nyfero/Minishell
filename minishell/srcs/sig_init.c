/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:15:59 by gsap              #+#    #+#             */
/*   Updated: 2022/03/20 19:20:40 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_main(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	if (sigemptyset(&sint.sa_mask))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (sigemptyset(&squit.sa_mask))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	sint.sa_handler = &sigint_main;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = &sigquit_main;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}

void	signal_child(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	if (sigemptyset(&sint.sa_mask))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (sigemptyset(&squit.sa_mask))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	sint.sa_handler = &sigint_child;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = &sigquit_child;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}

void	signal_here(void)
{
	struct sigaction	sint;
	struct sigaction	squit;

	if (sigemptyset(&sint.sa_mask))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (sigemptyset(&squit.sa_mask))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	sint.sa_handler = NULL;
	sint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = NULL;
	squit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &squit, NULL);
}
