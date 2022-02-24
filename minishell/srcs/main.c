/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/02/24 17:49:19 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	fonciton_exec(t_line **line, t_env **env)
{
	int		pid;
	int		res_child;
	char	**tmp;
	char	**env_tmp;
	t_line	*ptr;

	ptr = *line;
	while (ptr != NULL)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			tmp = ft_split_minishell(ptr->cmd, ' ');
			env_tmp = env_to_str(env);
			execve(tmp[0], tmp, env_tmp);
			ft_free_ls(tmp);
			ft_free_ls(env_tmp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&res_child);
			if (WIFEXITED(res_child))
			{
				if (WEXITSTATUS(res_child) == 1)
					printf("exec_failled\n");
				else
					printf("exec_succed\n");
			}
		}
		ptr = ptr->next;
	}
	return ;
}

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
	//init_signal();
	while (1)
	{
		inpt = readline("Prompt> ");
		if (!inpt)
		{
			destroy_env(&env);
			printf("exit\n");
			break ;
		}
		else
		{
			parsing(&line, inpt);
			if (line)
			{
				printf("line->cmd:%s\n", line->cmd);
				fonciton_exec(&line, &env);
				//if (check_builtin(line->cmd, &env))
				//	break ;
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
