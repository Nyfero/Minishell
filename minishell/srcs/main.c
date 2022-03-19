/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/19 14:02:30 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	t_line	*line;
	t_env	*env;

	del_arg(argc, argv);
	env = NULL;
	if (init_env(&env, envp))
		exit(1);
	while (1)
	{
	printf("-----init main signal\n");
		init_signal();
		line = NULL;
		inpt = readline("Prompt> ");
		if (!inpt)
			return (exit_ctr_d(env));
		else
		{
			parsing(&env, &line, inpt);
			if (line)
				exec_line(&line, &env, inpt);
			free(inpt);
		}
	}
	return (close_minishell(env));
}

int	close_minishell(t_env *env)
{
	clear_history();
	destroy_env(&env);
	return (0);
}

void	del_arg(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return ;
}

int	exit_ctr_d(t_env *env)
{
	ft_putendl_fd("exit", 1);
	destroy_env(&env);
	return (0);
}

void	exec_line(t_line **line, t_env **env, char *inpt)
{
	pipex_entry(*line, env);
	add_history(inpt);
	destroy_list_line(line);
}
