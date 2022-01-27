/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:12:58 by gsap              #+#    #+#             */
/*   Updated: 2022/01/26 15:35:02 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[10000];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
}
