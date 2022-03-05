/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:03:36 by gsap              #+#    #+#             */
/*   Updated: 2022/03/05 17:35:06 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Tant que j'ai des élément à unset je cherche dans env si c'est le premier
**	maillon ou pas et je le supprime
*/

int	ft_unset(char **str, t_env **env)
{
	t_env	*ptr;
	int		i;
	int		len;

	if (!*env)
		return (0);
	i = 0;
	while (str[++i])
	{
		ptr = ft_get_var(str[i], env);
		if (ptr)
			del_env_maillon(ptr, env);
	}
	return (0);
}

/*
**	Si c'est le premier élément je modifie le pointeur de *env pour qu'il pointe
**	sur le deuxième élément; sinon je fais sauter un maillon à mon pointeur
*/

void	del_env_maillon(t_env *ptr, t_env **env)
{
	t_env	*tmp;

	if (ptr == *env)
	{
		tmp = *env;
		*env = (*env)->next;
	}
	else
	{
		tmp = ptr->next;
		ptr->next = tmp->next;
	}
	tmp->next = NULL;
	free(tmp->name);
	free(tmp->var);
	free(tmp);
	return ;
}
