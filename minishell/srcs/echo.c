/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:53:48 by gsap              #+#    #+#             */
/*   Updated: 2022/02/01 16:51:26 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flags(char **str)
{
	int	i;
	int	j;
	int	flags;

	i = 1;
	flags = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-')
		{
			j++;
			while (str[i][j] == 'n')
				j++;
			if (str[i][j] == 0)
			{
				flags += 1;
				i++;
			}
			else
				return (ft_error("BAD FLAGS"));
		}
		return (flags);
	}
	return (ft_error("NO ARG"));
}

void	ft_echo(char **str)
{
	int	i;
	int	j;

	j = check_flags(str);
	if (j == -1)
		return ;
	i = j + 1;
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (j == 0)
		printf("\n");
	return ;
}
