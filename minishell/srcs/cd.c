/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:52:30 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/14 11:33:47 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
**!ft_strncmp(str, "--", 3) || !ft_strncmp(str, "~", 1) \
**				|| !ft_strncmp(str, "", 1)
**
**bash: cd: OLDPWD not set											erreur = 1
**bash: cd: sdfgyhuikjv: No such file or directory 					erreur = 1
**jgourlin@e2r4p15:~$ cd -re
**bash: cd: -r: invalid option  afficher premiere lettre apes '-' 	erreur = 2
**
**verifier si path valide apres car meme sortie cd?
**Verifier si DOSSIER (sinon error 1)
**
**Verifier droit exec
**
**cd "" = rien (juste gerer les PWD OLDPWD)
*/

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
		{
		//	printf("PATH = %s\n", res);
			return (res);
		}
		free(res);
		i++;
	}
	return (0);
}

int	ft_cd_path(char *path, t_env **env, char *str)
{
//	DIR	*fd;

	(void)path;
	(void)env;
	(void)str;

	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}

	printf("END FT_CD_PATH (changement OLDPWD et PWD ici)\n");
	if (ft_change_OLDPWD(env))
		return (1);
	if (ft_change_PWD(env))
		return (1);
	//changer PWD
	printf("SUB CHANGEMENT\n");

	//si existe dans env use = t_env	*mod_env_maillon(char *str, t_env *ptr, int flags)
	//sinon add fin avec = t_env	*create_env_maillon(char *str, int flags)
	return (0);
}

//PWD unset -> OLDPWD n'est pus visible env mais dans export si
//cd - = error unset
// si var = NULL et flags

// il revient apres normal dans env et export


int	ft_cd_alpha(char *str, t_env **env)
{
	t_env	*res;
	char	**cdpath;
	char	*temp;
	int		ret;

	(void)env;
	(void)str;
	if (!str || !ft_strncmp(str, "--", 3))
	{
		res = ft_get_var("HOME", *env);
		if (res)
		{
//			printf("NAME = %s\nVAR = %s\n", res->name, res->var);
			return (ft_cd_path(res->var, env, str));
		}
		else
		{
			printf("cd: HOME not set\n");/*OLDPWD n'existe pas*/
			return (1);
		}
	}
	else if (!ft_strncmp(str, "-", 2))
	{
		res = ft_get_var("OLDPWD", *env);
		if (!res || res->flags == 1 || res->flags == 3)/*Verifier si OLDPWD existe*/
		{
			printf("cd: OLDPWD not set\n\n"); /*OLDPWD n'existe pas*/
			return (1);
		}
		else /*OLDPWD existe*/
		{
//			printf("NAME = %s\nVAR = %s\n", res->name, res->var);
			return (ft_cd_path(res->var, env, str));
		}
	}
	else if (str[0] == '-')
	{
		printf("bash: cd: -%c: invalid option\n", str[1]);
		return (2);
	}
	else /*gerer cas $$ $LANG etc... Pas besoin : checker path*/
	{
		res = ft_get_var("CDPATH", *env);
		printf("salut res = %p\n", res);//a suppr
		if (res && str[0] != '.')
		{
			cdpath = ft_split(res->var, ':');
			if (!cdpath)
			{
				printf("malloc error cd.c\n");//a modifier
				//Cannot allocate memory
				return (12);
			}

			int i = 0;//a suppr
			while (cdpath[i])//a suppr
			{
				printf("cdpath[%d] = %s\n", i, cdpath[i]);
				i++;
			}

			temp = ft_cd_cdpath(str, cdpath);
			if (!temp)
			{
				printf("pas de chemin trouver avec cdpath\n");//suppr
			}
			else
			{
				printf("final CDPATH= %s\n", temp);//a suppr
				ret = ft_cd_path(temp, env, str);
				free(temp);
				return (ret);
			}
		}

		printf("sortie voire le cas : %s\nNormalelent cas PATH en param\n", str);//a suppr
		return (ft_cd_path(str, env, str));
	}
	return (0);
}

int	ft_cd(char **str, t_env **env)
{
	int	i;
	(void)env;
	(void)str;

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
printf("\nfin ft_cd\n\n");
	return (0);
}
