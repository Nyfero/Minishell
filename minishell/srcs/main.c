/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/02/04 17:30:47 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	char	buf[2];
	t_line	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	init_env(&env, envp);
	//init_signal();
	while (1)
	{
		inpt = readline("Prompt> ");
		printf("inpt =%s\n", inpt);
		if (!(inpt || *inpt))
		{
			// check si le fd 0 est fermé (ctr + D)
			if (read(0, buf, 1) == 0)
				break ;
		}
		else
		{
			line = parsing(inpt);
			if (check_builtin(line->cmd, &env))
				break ;
			add_history(inpt);
			minishell_del_list(line);
		}
		free(inpt);
	}
	free(inpt);
	rl_clear_history();
	return (0);
}
