/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/03/22 18:10:43 by jgourlin         ###   ########.fr       */
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
	int		ret_parsing;
	t_env	*ptr;
	int		test;

	ret_parsing = parse(env, line, inpt, bin);
	if (*line)
		if (check_only_redir(*line, env, inpt))
			ret_parsing = 2;
	ptr = ft_get_var("?", *env);
	test = ft_strncmp(ptr->var, "127", ft_strlen(ptr->var));
	if ((*line && ret_parsing != 2) || !test)
		exec_line(line, env);
	if (ret_parsing == 2 && test)
	{
		destroy_list_line(line);
	}
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

void	exec_line(t_line **line, t_env **env)
{
	t_env	*ptr;
	char	*tmp;

	tmp = NULL;
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
}
