/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:44:25 by gsap              #+#    #+#             */
/*   Updated: 2022/03/20 20:36:46 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_bin(t_garbage bin)
{
	bin.env = NULL;
	bin.line = NULL;
	bin.here = NULL;
	bin.cur_here = NULL;
	bin.inpt = NULL;
	bin.cmd = NULL;
}

void	free_bin(t_garbage bin)
{
	printf("child ptrbin = %p\n", &bin);
	printf("child ptrcmd = %p (%s)\n",bin.cmd, bin.cmd[0]);


	destroy_env(&bin.env);
	destroy_list_line(bin.line);
	destroy_dir(bin.here);
	free(bin.cur_here);
	ft_free_ls(bin.cmd);
	free(bin.inpt);
}
