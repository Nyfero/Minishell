/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:03:36 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 15:31:19 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	gestion d'erreur et a mettre au propre
*/

void	ft_unset(char **str, t_env **env)
{
	t_env	*ptr;
	t_env	*remove;
	char	*tmp;
	int		len;
	int		i;
	int		ret;

	ret = 0;
	if (!*env)
		return ;
	i = 1;
	while (str[i])
	{
		ptr = *env;
		tmp = ft_strjoin(str[i], "=");
		if (!tmp)
			return ;
		len = ft_strlen(tmp) + 1;
		if (ft_strncmp(tmp, ptr->name, len) == 0)
		{
			*env = ptr->next;
			ptr->next = NULL;
			free(ptr);
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
}
