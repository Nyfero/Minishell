/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:21:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/14 09:26:07 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char **cmd, char const *inpt)
{
	int	i;
	int	j;
	int	compt;

	if (check_nbr_pipe(cmd, inpt))
		return (1);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		compt = 0;
		while (cmd[i][++j])
		{
			if (!ft_isalnum(cmd[i][j]))
				compt++;
		}
		if ((size_t)compt == ft_strlen(cmd[i]))
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (1);
		}
	}
	return (0);
}

int	check_nbr_pipe(char **cmd, char const *inpt)
{
	int	compt;
	int	i;

	i = 0;
	compt = 0;
	while (inpt[i])
	{
		if (inpt[i] && inpt[i] == '|' && bool_not_in_quotes(inpt))
		{
			i++;
			compt++;
		}
		while (inpt[i] && (inpt[i] != '|'))
			i++;
	}
	if (compt != ft_lstrlen(cmd) - 1)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (1);
	}
	return (0);
}