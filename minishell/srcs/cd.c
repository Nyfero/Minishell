/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:52:30 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/07 11:50:15 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_var(char *search, t_env *env)
{
	if (!env || !search)
		return (0);//bash: cd: "search" not set
	if (!ft_strncmp(env->name, search, ft_strlen(search) + 1))
		return (env);
	return (ft_get_var(search, env->next));
}


//!ft_strncmp(str, "--", 3) || !ft_strncmp(str, "~", 1) || !ft_strncmp(str, "", 1)

//bash: cd: OLDPWD not set												erreur = 1
//bash: cd: sdfgyhuikjv: No such file or directory 						erreur = 1
//jgourlin@e2r4p15:~$ cd -re
//bash: cd: -r: invalid option     afficher premiere lettre apes '-' e	rreur = 2

//verifier si path valide apres car meme sortie cd?


//cd "" = rien (juste gerer les PWD OLDPWD)

int	ft_cd_alpha(char *str, t_env *env)
{
	(void)env;
	(void)str;
	t_env *res;

	if (!str)
	{
		printf("BRAVO_0\n");
		return (0);
	}
	if (!ft_strncmp(str, "-", 2))
	{
		printf("BRAVO_01 = %s\n", "str = \"-\"");

		//printf("ft_get_var == |%s|\n", ft_get_var("OLDPWD", env));
		res = ft_get_var("OLDPWD", env);
		if (!res)  //Verifier si OLDPWD existe 
		{
			printf("OLDPWD existe pas\n"); // attention si OLDPWD existe mais vide il va ici
			return (0);
		}
printf("NAME = %s\nVAR = %s\n", res->name, res->var);
//		else if ()//OLDPWD existe -- ft_get_var("OLDPWD", env) ?
//		{
//			if ()//OLDPWD non valide -- ft_valid_path
//			{
//				//bash: cd: xcfghjk/vghj: No such file or directory
//			}
//			else
//			{
//				
//			}
//		}
	}
	//else if (!str || str == '~' || str == "" || str == "--")
	else if (!str || !ft_strncmp(str, "--", 3))
	{
	//	printf("BRAVO_02 = %s\n", str);
	//	if ()//check home existe  -- ft_get_var("HOME", env) ?
	//	{
	//		if ()//home non valide -- ft_valid_path
	//		{
	//			//bash: cd: xcfghjk/vghj: No such file or directory
	//		}
	//		else
	//		{
	//			
	//		}
	//	}
	}
//	else ()//check_path valide -- ft_valid_path
//	{
//		
//	}
	else if (str[0] == '-' && str[1] != '-')
		printf("bash: cd: -%c: invalid option\n", str[1]);
	else
		printf("sortie %s\n\n", str);
		
	int i;

	i = 0;
	while (str[i])
		printf("str[i] == %d\n", str[i++]);
	return (0);
	
}

int	ft_cd(char **str, t_env *env)
{
	(void)env;
	(void)str;
	int	i;

	i = 0;
	while (str[i])
	{
		printf("str[%i] == %s\n", i, str[i]);
		i++;
	}
	if (i > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	ft_cd_alpha(str[1], env);
printf("\n");
	return (0);
	
	
	
}