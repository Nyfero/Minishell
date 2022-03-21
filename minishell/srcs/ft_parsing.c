/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 15:05:34 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_env **env, t_line **line, char const *inpt, t_garbage bin)
{
	char	**cmd;
	t_line	*ptr;
	int		i;

	cmd = ft_split_minishell(inpt, '|');
	i = check_inpt(cmd, inpt);
	if (i != 0)
		return (i - 1);
	bin.cmd = cmd;
	create_list_line(line, ft_lstrlen(cmd), env);
	if (!line)
		return (2);
	bin.line = line;
	ptr = *line;
	i = 0;
	while (ptr)
	{
		fill_line(cmd[i], ptr, env, bin);
		i++;
		ptr = ptr->next;
	}
	free(cmd);
	return (0);
}

int	check_builtin(t_line *line, t_env **env)
{
	char	**tmp;

	tmp = ft_split_minishell(line->cmd, ' ');
	if (ft_strncmp(tmp[0], "env", 4) == 0)
		return (ft_env(tmp, env, line));
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		return (ft_unset(tmp, env));
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		return (ft_export(tmp, env, line));
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		return (ft_cd(tmp, env));
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		return (ft_exit(tmp));
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		return (ft_pwd(line, tmp));
	else if (ft_strncmp(tmp[0], "echo", 5) == 0)
		return (ft_echo(tmp, line));
	ft_free_ls(tmp);
	return (-1);
}
