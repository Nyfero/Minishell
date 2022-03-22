/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:14:04 by gsap              #+#    #+#             */
/*   Updated: 2022/03/22 13:34:38 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **tmp, t_env **env, t_line *line)
{
	if (!tmp[1])
	{
		ft_free_ls(tmp);
		destroy_env(env);
		destroy_list_line(&line);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (ft_lstrlen(tmp) > 2)
	{
		ft_free_ls(tmp);
		ft_putendl_fd("exit : too many arguments", 2);
		return (1);
	}
	else
		exit(ft_exit_arg(tmp, env, line));
}

int	ft_exit_arg(char **str, t_env **env, t_line *line)
{
	int	i;

	i = -1;
	if (str[1][0] == '-' || str[1][0] == '+')
		i++;
	while (str[1][++i])
	{
		if (!ft_isdigit(str[1][i]))
		{
			ft_putstr_fd("exit : ", 2);
			ft_putstr_fd(str[1], 2);
			ft_putendl_fd(": numeric arguments required", 2);
			ft_free_ls(str);
			destroy_env(env);
			destroy_list_line(&line);
			return (2);
		}
	}
	ft_putendl_fd("exit", 1);
	i = ft_atoi(str[1]);
	while (i < 0)
		i += 256;
	if (i > 256)
		i = i % 256;
	ft_free_ls(str);
	destroy_env(env);
	destroy_list_line(&line);
	return (i);
}
