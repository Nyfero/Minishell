/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:12:58 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 17:25:15 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[10000];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return(1);
	}
	else
		printf("%s\n", cwd);
	return (0);
}
