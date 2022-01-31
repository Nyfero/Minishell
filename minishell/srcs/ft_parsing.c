/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/01/31 17:52:06 by gsap             ###   ########.fr       */
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
	printf("%d\n", ft_lstrlen(tmp));
	while (tmp[i])
	{
		minishell_addlist(&line, tmp[i]);
		i++;
	}
	ft_free_ls(tmp);
	return (line);
}
