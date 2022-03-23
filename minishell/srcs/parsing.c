/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/03/23 16:05:03 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

int	parsing(t_env **env, t_line **line, char const *inpt, t_garbage bin)
{
	char	**cmd;
	t_line	*ptr;
	int		i;

	cmd = ft_split_minishell(inpt, '|');
	i = check_inpt(cmd, inpt);
	if (i != 0)
		return (close_wrong_inpt(cmd, i - 1));
	bin.cmd = cmd;
	create_list_line(line, ft_lstrlen(cmd), env);
	if (!*line)
		return (close_wrong_inpt(cmd, 2));
	bin.line = line;
	ptr = *line;
	i = 0;
	while (ptr)
	{
		if (fill_line(cmd[i], ptr, env, bin))
			return (close_wrong_inpt(cmd, 2));
		i++;
		ptr = ptr->next;
	}
	ft_free_ls(cmd);
	return (0);
}

int	check_builtin(t_line *line, t_env **env, int x)
{
	char	**tmp;

	if (!line->cmd)
		return (-1);
	tmp = ft_split_minishell(line->cmd, ' ');
	if (!tmp[0])
	{
		free(tmp);
		return (-1);
	}
	else if (ft_strncmp(tmp[0], "env", 4) == 0)
		return (ft_env(tmp, env, line));
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		return (ft_unset(tmp, env));
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		return (ft_export(tmp, env, line));
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		return (ft_cd(tmp, env));
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		return (ft_exit(tmp, env, line, x));
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		return (ft_pwd(line, tmp));
	else if (ft_strncmp(tmp[0], "echo", 5) == 0)
		return (ft_echo(tmp, line));
	return (close_wrong_inpt(tmp, -1));
}

int	close_wrong_inpt(char **cmd, int i)
{
	if (cmd)
		ft_free_ls(cmd);
	return (i);
}

int	parse(t_env **env, t_line **line, char *inpt, t_garbage bin)
{
	t_env	*ptr;
	char	*tmp;
	int		ret_parsing;

	ptr = ft_get_var("?", *env);
	if (g_sig)
	{
		tmp = ft_itoa(g_sig);
		ptr = mod_env_maillon(tmp, ptr, 2);
		free(tmp);
	}
	g_sig = 0;
	ret_parsing = parsing(env, line, inpt, bin);
	tmp = ft_itoa(ret_parsing);
	if (ret_parsing)
		ptr = mod_env_maillon(tmp, ptr, 2);
	else
		ptr = mod_env_maillon("0", ptr, 2);
	free(tmp);
	if (inpt[0])
		add_history(inpt);
	reset_bin(bin);
	return (ret_parsing);
}

int	check_only_redir(t_line *line, t_env **env, char *inpt)
{
	t_env	*ptr;
	int		i;

	ptr = ft_get_var("?", *env);
	if (!line->cmd)
	{
		i = -1;
		while (inpt[++i])
		{
			if (inpt[i] == '\"' || inpt[i] == '\'')
			{
				ptr = mod_env_maillon("127", ptr, 2);
				return (0);
			}
		}
		ptr = mod_env_maillon("2", ptr, 2);
		return (1);
	}
	return (0);
}
