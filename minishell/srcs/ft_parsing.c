/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/02/01 16:06:16 by gsap             ###   ########.fr       */
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
	// while (line)
	// {
	// 	printf("cmd =>%s\n", line->cmd);
	// 	line = line->next;
	// }
	return (line);
}

int		check_builtin(char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split_minishell(str, ' ');
	while (tmp[i])
	{
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
