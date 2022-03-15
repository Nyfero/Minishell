/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:13:18 by gsap              #+#    #+#             */
/*   Updated: 2022/03/15 10:28:42 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_free_ls(char **ls)
{
	int	i;
	int	j;

	i = 0;
	j = ft_lstrlen(ls);
	while (i < j)
	{
		if (ls[i])
			free(ls[i]);
		i++;
	}
	if (ls)
		free(ls);
	return ;
}
