/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 16:25:39 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	main(int argc, char **argv, char **envp)
{
	char		*inpt;
	t_line		*line;
	t_env		*env;
	t_garbage	bin;

	env = NULL;
	if (init_env(&env, envp))
		exit(1);
	while (1)
	{
		g_sig = 0;
		signal_main();
		bin.env = env;
		line = NULL;
		inpt = readline("Prompt> ");
		bin.inpt = inpt;
		if (!inpt)
			return (exit_ctr_d(env));
		else
			parse_and_exec(&env, &line, inpt, bin);
	}
	return (close_minishell(env, argc, argv));
}

void	parse_and_exec(t_env **env, t_line **line, char *inpt, t_garbage bin)
{
	t_env	*ptr;
	char	*tmp;
	int		ret_parsing;

	ptr = ft_get_var("?", *env);
	ret_parsing = parsing(env, line, inpt, bin);
	printf("ret_parsing:%d\n", ret_parsing);
	tmp = ft_itoa(ret_parsing);
	if (ret_parsing || g_sig == 0)
		ptr = mod_env_maillon(tmp, ptr, 2);
	if (inpt[0])
		add_history(inpt);
	reset_bin(bin);
	if (*line && ret_parsing != 2)
	{
		tmp = NULL;
		exec_line(line, env);
	}
	free(tmp);
	free(inpt);
}

int	close_minishell(t_env *env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	clear_history();
	destroy_env(&env);
	return (0);
}

int	exit_ctr_d(t_env *env)
{
	ft_putendl_fd("exit", 1);
	clear_history();
	destroy_env(&env);
	return (0);
}

void    exec_line(t_line **line, t_env **env)
{
	t_env	*ptr;
	char	*tmp;

	ptr = ft_get_var("?", *env);
	tmp = ft_itoa(pipex_entry(*line, env));
	if (g_sig)
	{
		if (g_sig == 131)
			ft_putendl_fd("^\\Quit (core dumped)", 2);
		free(tmp);
		tmp = ft_itoa(g_sig);
	}
	ptr = mod_env_maillon(tmp, ptr, 2);
	free(tmp);
	destroy_list_line(line);
}
