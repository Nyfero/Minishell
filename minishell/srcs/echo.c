/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:53:48 by gsap              #+#    #+#             */
/*   Updated: 2022/03/14 09:38:24 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flags(char **str)
{
	int	i;
	int	j;
	int	flags;

	i = 0;
	flags = 0;
	while (str[++i])
	{
		j = 0;
		if (str[i][j] == '-')
		{
			j++;
			while (str[i][j] == 'n')
				j++;
			if (str[i][j] == 0)
				flags += 1;
		}
		else
			return (flags);
	}
	return (flags);
}

int	ft_echo(char **str, t_line *line)
{
	int	i;
	int	j;

	if (!str)
	{
		ft_putendl_fd("", line->outdir);
		return (0);
	}
	j = check_flags(str);
	i = j;
	while (str[++i])
	{
		ft_putstr_fd(str[i], line->outdir);
		if (str[i])
			ft_putstr_fd(" ", line->outdir);
	}
	if (j == 0)
		ft_putendl_fd("", line->outdir);
	return (0);
}
