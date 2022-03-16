/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/16 18:22:02 by gsap             ###   ########.fr       */
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
	if (init_env(&env, envp))
		exit(1);
	while (1)
	{
		init_signal();
		inpt = readline("Prompt> ");
		if (!inpt)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		else
		{
			printf("AMOUR\n");
			parsing(&env, &line, inpt);
			printf("HAINE\n");
			if (line)
			{
				pipex_entry(line, &env);
				add_history(inpt);
				destroy_list_line(&line);
			}
			free(inpt);
		}
	}
	clear_history();
	destroy_env(&env);
	return (0);
}
