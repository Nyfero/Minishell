/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:52:30 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/04 10:31:54 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var(char *search, t_env *env)
{
	if (!env)
		return (0);
	if (!ft_strncmp(env->name, search, ft_strlen(search) + 1))
		return (env->var);
	return (ft_get_path(search, env));
}

//bash: cd: OLDPWD not set
//bash: cd: sdfgyhuikjv: No such file or directory

//verifier si path valide apres car meme sortie cd?
int	ft_cd_alpha(char *str, t_env *env)
{
	if (str == '-')
	{
		//if () Verifier si OLDPWD existe 
		else if ()//OLDPWD existe
		{
			if ()//OLDPWD non valide
			{

			}
			else
			{
				
			}
		}
	}
	else if (!str || str == '~' || str == "")
	{
		if ()//check home existe
		{
			
		}
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