/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 14:22:51 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Pour gerer les ; il faut creer un tableau de line et faite un split sur ;
*/

t_line	*parsing(char *inpt)
{
	t_line	*line;
	char	**tmp;
	int		i;

	i = 0;
	line = NULL;
	tmp = ft_split_minishell(inpt, '|');
	while (tmp[i])
	{
		minishell_addlist(&line, tmp[i]);
		i++;
	}
	ft_free_ls(tmp);
	return (line);
}

int		check_builtin(char *str, t_env *env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split_minishell(str, ' ');
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "env", 4) == 0)
			ft_env(env);
		if (ft_strncmp(tmp[i], "unset", 6) == 0)
			ft_unset(tmp, &env);
		/*if (ft_strncmp(tmp[i], "cd", 3) == 0)
			ft_cd(tmp, env);*/
		if (ft_strncmp(tmp[i], "exit", 5) == 0)
			return (1);
		if (ft_strncmp(tmp[i], "pwd", 4) == 0)
			ft_pwd();
		if (ft_strncmp(tmp[i], "echo", 5) == 0)
			ft_echo(tmp);
		i++;
	}
	return (0);
}

int	not_in_quotes(char const *s)
{
	int	s_qt;
	int	d_qt;

	s_qt = 0;
	d_qt = 0;
	while (*s)
	{
		if (*s == 39)
			s_qt++;
		if (*s == 34)
			d_qt++;
		s++;
	}
	if (s_qt % 2 == 0 && d_qt % 2 == 0)
		return (1);
	return (0);
}
