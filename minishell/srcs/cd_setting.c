/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:22:12 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/22 14:10:18 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_last_env(t_env	*env)
{
	if (!env)
		return (0);
	if (env->next)
		return (ft_last_env(env->next));
	return (env);
}

int	ft_change_pwd_2(t_env **pwd, char *cwd, int i)
{
	*pwd = mod_env_maillon(cwd, *pwd, i);
	if (!*pwd)
		return (1);
	return (0);
}

int	ft_change_pwd(t_env **env)
{
	t_env	*pwd;
	t_env	*temp;
	char	*str;
	char	cwd[10000];

	pwd = ft_get_var("PWD", *env);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("");
		return (1);
	}
	if (!pwd)
	{
		temp = ft_last_env(*env);
		str = ft_strjoin("PWD=", cwd);
		if (!str)
			return (1);
		temp->next = create_env_maillon(str, 2);
		free(str);
	}
	else if (pwd->flags == 3 || pwd->flags == 2)
		return (ft_change_pwd_2(&pwd, cwd, 2));
	else if (pwd->flags == 0 || pwd->flags == 1)
		return (ft_change_pwd_2(&pwd, cwd, 0));
	return (0);
}

int	ft_change_oldpwd(t_env **env)
{
	t_env	*old;
	t_env	*pwd;
	t_env	*temp;
	char	*str;

	old = ft_get_var("OLDPWD", *env);
	pwd = ft_get_var("PWD", *env);
	if (!old)
	{
		temp = ft_last_env(*env);
		if (!pwd || pwd->flags % 2 == 1)
			temp->next = create_env_maillon("OLDPWD", 3);
		else
		{
			str = ft_strjoin("OLDPWD=", pwd->var);
			if (!str)
				return (1);
			temp->next = create_env_maillon(str, 2);
			free(str);
		}
		return (0);
	}
	return (ft_change_oldpwd_old_exist(env));
}
