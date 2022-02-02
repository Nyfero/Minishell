/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/02/02 11:29:30 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*inpt;
	char	buf[2];
	t_line	*line;
	t_env	*env;

	ft_getenv(&env, envp);
	init_signal();
	while (1)
	{
		inpt = readline("Prompt> ");
		// check si le fd 0 est fermé (ctr + D)
		if (!inpt && !*inpt)
		{
			if (read(0, buf, 1) == 0)
				break;
		}
		else
		{
			line = parsing(inpt);
			// renvoie 1 si exit est trouvé, 0 sinon et exécute le builtin
			if (check_builtin(line->cmd))
				break;
			add_history(inpt);
			minishell_del_list(line);
		}
		free(inpt);
	}
	free(inpt);
	rl_clear_history();
	return (0);
}
