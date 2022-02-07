/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/02/07 10:13:25 by gsap             ###   ########.fr       */
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

int	check_builtin(char *str, t_env **env)
{
	char	**tmp;
	int		ret;

	ret = 0;
	tmp = ft_split_minishell(str, ' ');
	if (ft_strncmp(tmp[0], "env", 4) == 0)
		ret = ft_env(tmp, env);
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		ret = ft_unset(tmp, env);
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		ret = ft_export(tmp, env);
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		ret = ft_cd(tmp, *env);
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		ret = ft_pwd();
	else if (ft_strncmp(tmp[0], "echo", 5) == 0)
		ret = ft_echo(tmp);
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
