/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/03/07 13:51:57 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_nbr_pipe(char **cmd, char const *inpt)
{
	int	compt;
	int	i;

	i = 0;
	compt = 0;
	while (inpt[i])
	{
		if (inpt[i] && (inpt[i] == '|') && not_in_quotes(inpt))
		{
			i++;
			compt++;
		}
		while (inpt[i] && (inpt[i] != '|'))
			i++;
	}
	if (compt != ft_lstrlen(cmd) - 1)
		return (1);
	return (0);
}

static int	check_pipe(char **cmd, char const *inpt)
{
	int	i;
	int	j;
	int	compt;

	if (check_nbr_pipe(cmd, inpt))
		return (1);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		compt = 0;
		while (cmd[i][++j])
		{
			if (!ft_isalnum(cmd[i][j]))
				compt++;
		}
		if ((size_t)compt == ft_strlen(cmd[i]))
			return (1);
	}
	return (0);
}

void	parsing(t_env **env, t_line **line, char const *inpt)
{
	char	**cmd;
	t_line	*ptr;
	int		i;

	if (!inpt)
		return ;
	cmd = ft_split_minishell(inpt, '|');
	if (ft_strncmp(cmd[0], inpt, ft_strlen(inpt)))
	{
		if (check_pipe(cmd, inpt))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return ;
		}
	}
	create_list_line(line, ft_lstrlen(cmd), env);
	ptr = *line;
	i = 0;
	while (ptr != NULL)
	{
		fill_line(cmd[i], ptr, ft_expand(cmd[i], env));
		i++;
		ptr = ptr->next;
	}
	ft_free_ls(cmd);
	return ;
}

int	check_builtin(t_line *line, t_env **env)
{
	char	**tmp;
	int		ret;

	ret = 0;
	tmp = ft_split_minishell(line->cmd, ' ');

printf("tmp[0] = %s\n", tmp[0]);//a suppr

	if (ft_strncmp(tmp[0], "env", 4) == 0)
		return (ft_env(tmp, env, line));
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		return (ft_unset(tmp, env));
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		return (ft_export(tmp, env, line));
	/*else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		return (ft_cd(tmp, env);
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		return (ft_exit(tmp));
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		return (ft_pwd(line));
	else if (ft_strncmp(tmp[0], "echo", 5) == 0)
		return (ft_echo(tmp, line));*/
	ft_free_ls(tmp);
	return (-1);
}
