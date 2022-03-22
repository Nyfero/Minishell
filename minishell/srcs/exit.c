/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:14:04 by gsap              #+#    #+#             */
/*   Updated: 2022/03/22 19:06:11 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **tmp, t_env **env, t_line *line, int x)
{
	if (!tmp[1])
	{
		if (!x)
		{
			ft_putendl_fd("exit", 1);
			clean_exit_memory(tmp, env, line, x);
			exit(0);
		}
		ft_free_ls(tmp);
		return (0);
	}
	else if (ft_lstrlen(tmp) > 2)
	{
		ft_free_ls(tmp);
		ft_putendl_fd("exit : too many arguments", 2);
		return (1);
	}
	else
	{
		if (!x)
			exit(ft_exit_arg(tmp, env, line, x));
		return (ft_exit_arg(tmp, env, line, x));
	}
}

int	ft_exit_arg(char **str, t_env **env, t_line *line, int x)
{
	int	i;

	i = -1;
	if (str[1][0] == '-' || str[1][0] == '+')
		i++;
	while (str[1][++i])
	{
		if (!ft_isdigit(str[1][i]))
		{
			print_error_exit(str[1]);
			clean_exit_memory(str, env, line, x);
			return (2);
		}
	}
	ft_putendl_fd("exit", 1);
	i = ft_atoi(str[1]);
	clean_exit_memory(str, env, line, x);
	while (i < 0)
		i += 256;
	if (i > 256)
		i = i % 256;
	return (i);
}

void	clean_exit_memory(char **str, t_env **env, t_line *line, int x)
{
	ft_free_ls(str);
	if (x == 0)
	{
		destroy_env(env);
		destroy_list_line(&line);
	}
}

void	print_error_exit(char *str)
{
	ft_putstr_fd("exit : ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric arguments required", 2);
}
