/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/02/24 11:21:47 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	t_line	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	line = NULL;
	env = NULL;
	init_env(&env, envp);
	char **tmp = env_to_str(&env);
	int i = -1;
	while (tmp[++i])
		printf("tmp[%d] = %s\n", i, tmp[i]);
	//init_signal();
	while (1)
	{
		inpt = readline("Prompt> ");
		if (!inpt)
		{
			printf("exit\n");
			break ;
		}
		else
		{
			parsing(&line, &env, inpt);
			//if (line)
			//{
			//	if (check_builtin(line->cmd, &env))
			//		break ;
			//	add_history(inpt);
			//	deallocate(&line);
			//}
		}
		free(inpt);
	}
	free(inpt);
	clear_history();
	return (0);
}
