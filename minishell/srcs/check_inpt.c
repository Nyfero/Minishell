/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inpt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 09:21:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/26 19:36:56 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_inpt(char **cmd, char const *inpt)
{
	if (!cmd || inpt[ft_strlen(inpt) - 1] == '|')
	{
		if (inpt[0] && inpt[ft_strlen(inpt) - 1] == '|')
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (3);
		}
		return (1);
	}
	if (!cmd[0])
	{
		free(cmd[0]);
		return (1);
	}
	if (check_space(cmd))
		return (1);
	if (check_quotes(inpt))
		return (3);
	if (ft_strncmp(cmd[0], inpt, ft_strlen(inpt)))
		if (check_pipe(cmd, inpt))
			return (3);
	return (0);
}

int	check_space(char **cmd)
{
	char	**tmp;

	tmp = ft_split(cmd[0], ' ');
	if (!tmp[0])
	{
		free(tmp);
		return (1);
	}
	ft_free_ls(tmp);
	return (0);
}

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
			if (cmd[i][j] == ' ' || cmd[i][j] == ';')
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
			compt++;
		i++;
	}
	if (compt != ft_lstrlen(cmd) - 1)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (1);
	}
	return (0);
}

int	check_quotes(char const *inpt)
{
	int	i;
	int	compt_1;
	int	compt_2;

	i = 0;
	compt_1 = 0;
	compt_2 = 0;
	while (inpt[i])
	{
		if (inpt[i] == '\'' && (compt_2 % 2) == 0)
			compt_1++;
		if (inpt[i] == '\"' && (compt_1 % 2) == 0)
			compt_2++;
		i++;
	}
	if ((compt_1 % 2) || (compt_2 % 2))
	{
		ft_putendl_fd("syntax error near `'' or `\"'", 2);
		return (1);
	}
	return (0);
}
