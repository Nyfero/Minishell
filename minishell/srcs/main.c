/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/01/26 17:46:59 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*inpt;

	while (1)
	{
		inpt = readline("> ");
		/*if (!check_builtin(inpt))
			check_path(inpt);*/
		if (ft_strncmp(inpt, "exit", 5) == 0)
			break;
		if (ft_strncmp(inpt, "pwd", 4) == 0)
			ft_pwd();
		if (ft_strncmp(inpt, "echo", 5) == 0)
			ft_echo(0, inpt);
		if (inpt && *inpt)
			add_history(inpt);
		free(inpt);
		rl_on_new_line();
	}
	free(inpt);
	rl_clear_history();
	return (0);
}
