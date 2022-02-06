/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:41:33 by gsap              #+#    #+#             */
/*   Updated: 2022/02/04 16:47:42 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Valeurs de retour de export:
**	0 tout c'est bien passé
**	1 not a valid identifier
**	2 bad flags ou syntax error near
*/

int	ft_export(char **str, t_env **env)
{
	t_env	*ptr;
	int		i;

	if (!*env)
		return (1);
	i = 1;
	if (!str[i])
		ft_export_no_arg(env);
	else
	{
		ptr = *env;
		while (ptr->next)
			ptr = ptr->next;
		while (str[i]/* && bool_check_valid(str[i], env)*/)
		{
			ptr->next = create_env_maillon(str[i], 0);
			ptr = ptr->next;
			i++;
		}
	}
	return (0);
}

void	ft_export_no_arg(t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ptr->flags < 2)
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->var);
		ptr = ptr->next;
	}
	return ;
}

/*int	bool_check_valid(char *str, t_env **env)
{
	t_env	*ptr;
	int		i;


}*/
