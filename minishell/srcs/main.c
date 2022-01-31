/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/01/31 18:18:23 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*inpt;
	char	buf[2];
	t_line	*line;

	init_signal();
	while (1)
	{
		inpt = readline("> ");

		/*if (!check_builtin(inpt))
			check_path(inpt);*/
		if (!inpt && !*inpt)
		{
			if (read(0, buf, 1) == 0)
			{
				printf("exit\n");
				break;
			}
		}
		else
			line = parsing(inpt);
		while (line)
		{
			printf("cmd = %s\n", line->cmd);
			line = line->next;
		}
		minishell_del_list(line);
		if (ft_strncmp(inpt, "exit", 5) == 0)
			break;
		if (ft_strncmp(inpt, "pwd", 4) == 0)
			ft_pwd();
		if (ft_strncmp(inpt, "echo", 5) == 0)
			ft_echo(inpt);
		if (ft_strncmp(inpt, "echo -n", 8) == 0)
			ft_echo_n(inpt);
		if (inpt && *inpt)
			add_history(inpt);
		free(inpt);
		rl_on_new_line();
	}
	free(inpt);
	rl_clear_history();
	return (0);
}
