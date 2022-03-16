/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/16 13:49:18 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glo	g_glo;

int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	t_line	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	line = NULL;
	env = NULL;
	g_glo.status = 0;
	g_glo.ret = 0;
	if (init_env(&env, envp))
		exit(1);
	//init_signal();
	while (1)
	{
		init_signal();
		inpt = readline("Prompt> ");
		if (g_glo.status == 1 && inpt)
		{

		}
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
				printf("line->in:%d\nline->out:%d\n", line->indir, line->outdir);
				pipex_entry(line, &env);
				add_history(inpt);
				destroy_list_line(&line);
			}
			free(inpt);
		}
		g_glo.status = 0 ;
	}
	clear_history();
	destroy_env(&env);
	return (0);
}
