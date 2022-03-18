/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:20:03 by gsap              #+#    #+#             */
/*   Updated: 2022/03/18 17:51:56 by gsap             ###   ########.fr       */
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

int	ft_env(char **str, t_env **env, t_line *line)
{
	t_env	*ptr;

	ptr = *env;
	if (!ptr)
		return (1);
	if (ft_lstrlen(str) > 1)
	{
		ft_putstr_fd("env: '", 2);
		print_error_wrpath(str[1]);
		ft_free_ls(str);
		return (1);
	}
	while (ptr)
	{
		if (ptr->flags == 0)
		{
			ft_putstr_fd(ptr->name, line->outdir);
			ft_putstr_fd("=", line->outdir);
			ft_putendl_fd(ptr->var, line->outdir);
		}
		ptr = ptr->next;
	}
	ft_free_ls(str);
	return (0);
}

/*
**	Créer une copie de t_env sous forme de (char **)
*/

char	**env_to_str(t_env **env)
{
	char	**tmp;
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = *env;
	if (!ptr)
		return (NULL);
	while (ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	tmp = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	ptr = *env;
	while (ptr->next)
	{
		tmp[i] = ft_strjoin(ptr->name, "=");
		if (ptr->var)
			tmp[i] = ft_strjoin_and_free_s1(tmp[i], ptr->var);
		i++;
		ptr = ptr->next;
	}
	return (tmp);
}

/*
**	Met un flag 1 si envp ne contient pas de '='
*/

t_env	*chose_flags(char *envp, t_env *ptr)
{
	if (format_key_value(envp) == 0)
		ptr = create_env_maillon(envp, 0);
	else
		ptr = create_env_maillon(envp, 1);
	return (ptr);
}
