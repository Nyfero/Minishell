/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:52:30 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/21 23:16:00 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cd_cdpath(char *str, char **path)
{
	int		i;
	char	*test;
	char	*res;

	i = 0;
	if (!path || path[0] == 0)
		return (0);
	while (path[i])
	{
		test = ft_strjoin(path[i], "/");
		if (!test)
			return (0);
		res = ft_strjoin(test, str);
		free(test);
		if (!res)
			return (0);
		if (access(res, F_OK | X_OK) == 0 && ft_file_access(res) == -1)
			return (res);
		free(res);
		i++;
	}
	return (0);
}

int	ft_cd_path(char *path, t_env **env, char *str)
{
	(void)path;
	(void)env;
	(void)str;
	if (chdir(path) == -1)
		return (ft_cd_error_double(path, strerror(errno)));
	if (ft_change_oldpwd(env))
		return (1);
	if (ft_change_pwd(env))
		return (1);
	return (0);
}

int	ft_cd_parse_2(char *str, t_env **env)
{
	char	**cdpath;
	char	*temp;
	int		ret;
	t_env	*res;

	res = ft_get_var("CDPATH", *env);
	if (res && str[0] != '.' && str[0] != '/')
	{
		cdpath = ft_split(res->var, ':');
		if (!cdpath)
			return (ft_error("Malloc failed\n"));
		temp = ft_cd_cdpath(str, cdpath);
		if (temp)
		{
			ret = ft_cd_path(temp, env, str);
			free(temp);
			return (ret);
		}
	}
	return (ft_cd_path(str, env, str));
}

int	ft_cd_parse(char *str, t_env **env)
{
	t_env	*res;

	if (!str || !ft_strncmp(str, "--", 3))
	{
		res = ft_get_var("HOME", *env);
		if (res)
			return (ft_cd_path(res->var, env, str));
		else
			return (ft_error("cd: HOME not set\n"));
	}
	else if (!ft_strncmp(str, "-", 2))
	{
		res = ft_get_var("OLDPWD", *env);
		if (!res || res->flags == 1 || res->flags == 3)
			return (ft_error("cd: OLDPWD not set\n"));
		else
			return (ft_cd_path(res->var, env, str));
	}
	else if (str[0] == '-')
		return (ft_cd_error_char(str[1]));
	else
		return (ft_cd_parse_2(str, env));
	return (0);
}

int	ft_cd(char **str, t_env **env)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 2)
	{
		ft_free_ls(str);
		return (ft_error("bash: cd: too many arguments\n"));
	}
	ft_cd_parse(str[1], env);
	ft_free_ls(str);
	return (0);
}
