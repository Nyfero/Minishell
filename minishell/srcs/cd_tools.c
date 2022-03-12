/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:22:12 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/09 18:15:00 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//si existe dans env use = t_env	*mod_env_maillon(char *str, t_env *ptr, int flags)
	//sinon add fin avec = t_env	*create_env_maillon(char *str, int flags)

t_env	*ft_last_env(t_env	*env)
{
	if (!env)
		return (0);
	if (env->next)
		return (ft_last_env(env->next));
	return (env);
}

void	ft_change_OLDPWD(t_env **env)
{
	t_env	*old;
	t_env	*pwd;
	t_env	*temp;

	old = ft_get_var("OLDPWD", *env);
	pwd = ft_get_var("PWD", *env);
	if (!old)//unset creer
	{
		temp = ft_last_env(*env);
		if (!pwd || pwd->flags % 2 == 1)// pwd == 1 / 3
		{
			create_env_maillon(temp,"OLDPWD", 3);

			//3
		}
		else // 0 / 2
		{
			create_env_maillon(temp, wd->var, 2);
			//2
		}
	}
	else if (old->flags % 2 == 1)// old pwd == 1 / 3
	{
		if (!pwd ||pwd->flags % 2 == 1)// pwd == 1 / 3
		{
			old = mod_env_maillon("", old, old->flags);
			if (!old)
				return (1);
			//old inchange
		}
		else
		{
			old = mod_env_maillon(pwd->var, old, old->flags - 1);
			if (!old)
				return (1);
			//3 = 2
			//1 = 0
		}
	}
	else if (old->flags % 2 == 0)//old == 0 / 2
	{
		if (pwd->flags % 2 == 1)// pwd == 1 / 3
		{
			old = mod_env_maillon("", old, old->flags + 1);
			if (!old)
				return (1);
			//flags + 1	
		}
		else // 0 / 2
		{
			old = mod_env_maillon(pwd->var, old, old->flags);
			if (!old)
				return (1);
			//inchange
		}
	}
}
