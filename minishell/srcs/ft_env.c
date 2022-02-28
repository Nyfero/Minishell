/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:20:03 by gsap              #+#    #+#             */
/*   Updated: 2022/02/28 10:44:46 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Valeurs de retour de env:
**	0 tout s'est bien passé
**	1 le paramètre est un fichier existant dans le current dir pas d'affichage
**	2 ../minishell/test: 1: test: 1: unexpected operator
**	126 permission denied
**	127 le paramètre donné est invalide
*/

int	ft_env(char **str, t_env **env)
{
	t_env	*ptr;
	int		ret;

	if (ft_lstrlen(str) > 1)
	{
		ret = ft_env_arg(str);
		if (ret)
			return (ret);
	}
	ptr = *env;
	while (ptr)
	{
		if (ptr->flags == 0)
			printf("%s=%s\n", ptr->name, ptr->var);
		ptr = ptr->next;
	}
	return (0);
}

int	ft_env_arg(char **str)
{
	char	**tmp;
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_strncmp(str[i], "env", 4) == 0)
			i++;
		else
		{
			tmp = ft_split((const char *)str[i], '"');
			if (tmp[0])
			{
				if (ft_lstrlen(tmp) == 1)
					printf("env: '%s' %s\n", tmp[0], WR_PATH);
				else
					printf("env: '%s' %s\n", tmp[1], WR_PATH);
			}
			else
				printf("env: '' %s\n", WR_PATH);
			ft_free_ls(tmp);
			return (1);
		}
	}
	return (0);
}
