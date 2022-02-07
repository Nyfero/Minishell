/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:52:30 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/07 15:59:51 by jgourlin         ###   ########.fr       */
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
//Verifier si DOSSIER (sinon error 1)

//Verifier droit exec

//cd "" = rien (juste gerer les PWD OLDPWD)

int	ft_cd_path(char *path, t_env *env, char *str)
{
	(void)path;
	(void)env;
	DIR	*fd;

	printf("path = %s\n", path);
	fd = opendir(path);
	if (fd == 0 && errno == 20)
	{
		printf("OPEN\n");
		printf("errno = %d\n", errno);
		printf("cd: %s: %s\n", strerror(errno), str);
		return (1);
	}
	if (fd == 0)
		closedir(fd);
	if (access(path, X_OK | F_OK) != 0)
	{
		printf("ACCES\n");
		printf("cd: %s: %s\n", strerror(errno), str);
		return (1);
	}
	printf("acces possible a -%s-\n", path);
	return (0);
}

int	ft_cd_alpha(char *str, t_env *env)
{
	(void)env;
	(void)str;
	t_env *res;

//if (!str || str == '~' || str == "" || str == "--")
	if (!str || !ft_strncmp(str, "--", 3))
	{
		res = ft_get_var("HOME", env);
		if (res)//check home existe
		{
			printf("NAME = %s\nVAR = %s\n", res->name, res->var);
			ft_cd_path(res->var, env, str);
		//check si path valide etc
		//faire comme si "cd res->var"
		//si var = "" ne pas bouger
//			if ()//home non valide -- ft_valid_path
//			{
//				//bash: cd: xcfghjk/vghj: No such file or directory
//			}
//			else
//			{
//				
//			}
		}
		else
		{
			printf("HOME existe pas\n"); //OLDPWD n'existe pas
			return (1);
		}
	}
	else if (!ft_strncmp(str, "-", 2))
	{
		res = ft_get_var("OLDPWD", env);
		if (!res)  //Verifier si OLDPWD existe 
		{
			printf("OLDPWD existe pas\n"); //OLDPWD n'existe pas
			return (1);
		}
		else //OLDPWD existe 
		{
			printf("NAME = %s\nVAR = %s\n", res->name, res->var);
			ft_cd_path(res->var, env, str);
	//faire comme si "cd res->var"
	//si var = "" == ne pas bouger
//			if ()//OLDPWD non valide -- ft_valid_path
//			{
//				//bash: cd: xcfghjk/vghj: No such file or directory
//			}
//			else
//			{
//				
//			}
		}
	}
	else if (str[0] == '-')
	{
		printf("bash: cd: -%c: invalid option\n", str[1]);
		return (2);
	}
	else //gerer cas $$ $LANG etc... Pas besoin : checker path
	{
		printf("sortie voire le cas : %s\n\n", str);
		ft_cd_path(str, env, str);
		return (0);
	}
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
//	ft_cd_alpha(str[1], env);
printf("\nfin ft_cd\n\n");
	return (0);
}
