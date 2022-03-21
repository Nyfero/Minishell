/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:10:59 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/21 19:08:55 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	//printf("bash: cd: %s: %s\n", path, strerror(errno));

int	ft_cd_error_double(char *s1, char *s2)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (1);
	res = ft_strjoin_and_free_s2("bash: cd: ", res);
	if (!res)
		return (1);
	res = ft_strjoin_and_free_all(res, s1);
	if (!res)
		return (1);
	res = ft_strjoin_and_free_s1(res, ": ");
	if (!res)
		return (1);
	res = ft_strjoin_and_free_s1(res, s2);
	if (!res)
		return (1);
	res = ft_strjoin_and_free_s1(res, "\n");
	if (!res)
		return (1);
	write(2, res, ft_strlen(res));
	return (1);
}

int	ft_cd_error_char(char c)
{
	char	*res;
	char	*big_c;

	res = ft_strdup("");
	if (!res)
		return (1);
	res = ft_strjoin_and_free_s2("bash: cd: -", res);
	if (!res)
		return (1);
	big_c = malloc(sizeof(char) * 2);
	if (!big_c)
	{
		free(res);
		return (1);
	}
	big_c[0] = c;
	big_c[1] = 0;
	res = ft_strjoin_and_free_all(res, big_c);
	if (!res)
		return (1);
	res = ft_strjoin_and_free_s1(res, ": invalid option\n");
	if (!res)
		return (1);
	write(2, res, ft_strlen(res));
	return (2);
}

int	ft_change_oldpwd_pwd(t_env **old, int flags, char *var)
{
	*old = mod_env_maillon(var, *old, flags);
	if (!old)
		return (1);
	return (0);
}

int	ft_change_oldpwd_npwd(t_env **old, int flags)
{
	printf("PWD autre\n");
	*old = mod_env_maillon("", *old, flags);
	if (!old)
		return (1);
	return (0);
}

int	ft_change_oldpwd_old_exist(t_env **env)
{
	t_env	*old;
	t_env	*pwd;

	old = ft_get_var("OLDPWD", *env);
	pwd = ft_get_var("PWD", *env);
	if (old->flags % 2 == 1)
	{
		if (!pwd || pwd->flags % 2 == 1)
			return (ft_change_oldpwd_npwd(&old, old->flags));
		else
			return (ft_change_oldpwd_pwd(&old, old->flags - 1, pwd->var));
	}
	else if (old->flags % 2 == 0)
	{
		if (!pwd || pwd->flags % 2 == 1)
			return (ft_change_oldpwd_npwd(&old, old->flags + 1));
		else
			return (ft_change_oldpwd_pwd(&old, old->flags, pwd->var));
	}
	return (0);
}
