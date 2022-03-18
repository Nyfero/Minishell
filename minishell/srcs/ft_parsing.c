/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/03/18 17:08:35 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env **env, t_line **line, char const *inpt)
{
	char	**cmd;
	t_line	*ptr;
	int		i;

	if (inpt[0] == 0)
		return ;
	cmd = ft_split_minishell(inpt, '|');
	if (!cmd[0])
		return ;
	if (ft_strncmp(cmd[0], inpt, ft_strlen(inpt)))
		if (check_pipe(cmd, inpt))
			return ;
	if (check_quotes(inpt))
		return ;
	create_list_line(line, ft_lstrlen(cmd), env);
	if (!line)
		return ;
	ptr = *line;
	i = 0;
	while (ptr)
	{
		fill_line(cmd[i], ptr, env);
		i++;
		ptr = ptr->next;
	}
	free(cmd);
	return ;
}

int	check_builtin(t_line *line, t_env **env)
{
	char	**tmp;

	tmp = ft_split_minishell(line->cmd, ' ');
	printf("len_tmp:%d\n", ft_lstrlen(tmp));
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
