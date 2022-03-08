/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:12:58 by gsap              #+#    #+#             */
/*   Updated: 2022/03/08 14:33:20 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_line *line)
{
	char	cwd[10000];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd() error");
		return (1);
	}
	else
		ft_putendl_fd(cwd, line->outdir);
	return (0);
}
