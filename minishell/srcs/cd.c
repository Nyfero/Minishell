/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:52:30 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/04 12:17:23 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var(char *search, t_env *env)
{
	if (!env)
		return (0);//bash: cd: "search" not set
	if (!ft_strncmp(env->name, search, ft_strlen(search) + 1))
		return (env->var);
	return (ft_get_path(search, env->next));
}

//bash: cd: OLDPWD not set
//bash: cd: sdfgyhuikjv: No such file or directory

//verifier si path valide apres car meme sortie cd?
int	ft_cd_alpha(char *str, t_env *env)
{
	if (str == '-')
	{
		//if () Verifier si OLDPWD existe 
		else if ()//OLDPWD existe -- ft_get_var("OLDPWD", env) ?
		{
			if ()//OLDPWD non valide -- ft_valid_path
			{
				//bash: cd: xcfghjk/vghj: No such file or directory
			}
			else
			{
				
			}
		}
	}
	else if (!str || str == '~' || str == "")
	{
		if ()//check home existe  -- ft_get_var("HOME", env) ?
		{
			if ()//home non valide -- ft_valid_path
			{
				//bash: cd: xcfghjk/vghj: No such file or directory
			}
			else
			{
				
			}
		}
	}
	else ()//check_path valide -- ft_valid_path
	{
		
	}
	
}

int	ft_cd(char **str, t_env *env)
{
	if (!str[2])
	{
		printf("bash: cd: too many arguments\n");
		return (2);
	}
	ft_cd_alpha(str[1], env);
	
	
	
}