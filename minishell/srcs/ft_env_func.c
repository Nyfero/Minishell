/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:30:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/01 10:49:39 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Créer une liste chainée de t_env
*/

void	init_env(t_env **env, char **envp)
{
	int		i;
	t_env	*ptr;

	i = -1;
	while (envp[++i])
	{
		if (!*env)
			*env = create_env_maillon(envp[i], 0);
		else
		{
			ptr = *env;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = create_env_maillon(envp[i], 0);
		}
	}
}

/*
**	Créer un maillon de t_env et le rempli avec un élément de l'environnement
*/

t_env	*create_env_maillon(char *str, int flags)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = ft_calloc(sizeof(t_env), 1);
	if (!tmp)
	{
		printf("MALLOC FAILED\n");
		exit(1);
	}
	i = 0;
	while (str[i] != '=')
		i++;
	j = i + 1;
	while (str[j])
		j++;
	tmp->name = ft_substr(str, 0, i);
	tmp->var = ft_substr(str, i + 1, j);
	tmp->flags = flags;
	tmp->next = NULL;
	return (tmp);
}

/*
**	Modifie la variable "var" d'un maillon de t_env
*/

t_env	*mod_env_maillon(char *str, t_env *ptr, int flags)
{
	int	i;

	if (ptr->var)
		free(ptr->var);
	ptr->var = NULL;
	ptr->flags = flags;
	i = 0;
	while (str[i] != '=')
		i++;
	ptr->var = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	return (ptr);
}

/*
**	Supprime la liste chainée t_env
*/

void	destroy_env(t_env **env)
{
	t_env	*ptr;
	t_env	*aux;

	ptr = *env;
	while (ptr != NULL)
	{
		aux = ptr;
		ptr = ptr->next;
		free(aux->name);
		free(aux->var);
		aux->next = NULL;
		free(aux);
	}
	*env = NULL;
}

/*
**	Retourne un pointeur sur l'élément cherché dans t_env s'il existe, 0 sinon
*/

t_env	*ft_get_var(char *search, t_env *env)
{
	if (!env || !search)
		return (0);//bash: cd: "search" not set
	if (!ft_strncmp(env->name, search, ft_strlen(search) + 1))
		return (env);
	return (ft_get_var(search, env->next));
}
