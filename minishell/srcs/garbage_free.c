/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:44:25 by gsap              #+#    #+#             */
/*   Updated: 2022/03/26 19:51:36 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_bin(t_garbage bin)
{
	bin.env = NULL;
	bin.inpt = NULL;
	bin.cmd = NULL;
	bin.line = NULL;
	bin.expand = NULL;
}

void	free_bin(t_garbage bin)
{
	destroy_env(&bin.env);
	free(bin.inpt);
	ft_free_ls(bin.cmd);
	destroy_list_line(bin.line);
	free(bin.expand);
}
