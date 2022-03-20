/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/20 16:18:56 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	t_line	*line;
	t_env	*env;

	rm_rf_arg(argc, argv);
	env = NULL;
	if (init_env(&env, envp))
		exit(1);
	while (1)
	{
		g_sig = 0;
		init_signal();
		line = NULL;
		inpt = readline("Prompt> ");
		printf("joe\n");
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

void	rm_rf_arg(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	close_minishell(t_env *env)
{
	clear_history();
	destroy_env(&env);
	return (0);
}

int	exit_ctr_d(t_env *env)
{
	ft_putendl_fd("exit", 1);
	destroy_env(&env);
	return (0);
}

void	exec_line(t_line **line, t_env **env, char *inpt)
{
	t_env	*ptr;
	char	*tmp;

	ptr = ft_get_var("?", *env);
	tmp = ft_itoa(pipex_entry(*line, env));
	if (g_sig)
	{
		free(tmp);
		tmp = ft_itoa(g_sig);
	}
	ptr = mod_env_maillon(tmp, ptr, 2);
	free(tmp);
	add_history(inpt);
	destroy_list_line(line);
}
