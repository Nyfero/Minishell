/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:03:36 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 19:14:54 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	gestion d'erreur et a mettre au propre NIQUE LE PREMIER ELEMENT
*/

int	ft_unset(char **str, t_env **env)
{
	t_env	*ptr;
	t_env	*remove;
	char	*tmp;
	int		len;
	int		i;

	if (!env)
		return (1);
	i = 1;
	printf("addresse de env : %p\n", *env);
	while (str[i])
	{
		ptr = *env;
		tmp = ft_strjoin(str[i], "=");
		if (!tmp)
			return (1);
		len = ft_strlen(tmp) + 1;
		if (ft_strncmp(tmp, ptr->name, len) == 0)
		{
			remove = ptr->next;
			printf("test perso %s\n", (*env)->name);
			printf("2e test %s\n", (*env)->next->name);
			printf("addresse de env %p\n", *env);
			*env = remove;
			printf("addresse de env %p\n", *env);
			//ptr->next = NULL;
			//free(ptr);
		}
		else
		{
			while (ptr->next)
			{
				if (ft_strncmp(tmp, ptr->next->name, len) == 0)
				{
					remove = ptr->next;
					ptr->next = remove->next;
					remove->next = NULL;
					free(remove);
				}
				ptr = ptr->next;
			}
		}
		free(tmp);
		i++;
	}
	return (0);
}

// void	del_env_maillon(t_env **env, t_env *ptr)
// {
//
// }
