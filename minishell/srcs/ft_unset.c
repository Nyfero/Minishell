/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:03:36 by gsap              #+#    #+#             */
/*   Updated: 2022/03/07 11:28:56 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **str, t_env **env)
{
	t_env	*ptr;
	int		i;

	if (!*env)
		return (0);
	i = 0;
	while (str[++i])
	{
		if (!check_meta(str[i]))
		{
			ptr = ft_get_var(str[i], *env);
			if (ptr)
				del_env_maillon(ptr, env);
		}
	}
	return (0);
}

int	check_meta(char *s)
{
	int	i;

	i = -1;
	if (ft_isdigit(s[0]))
	{
		ft_putstr_fd("unset : '", 2);
		print_error_idf(s);
		return (1);
	}
	while (s[++i])
	{
		if (!ft_isalnum(s[i]))
		{
			ft_putstr_fd("unset : '", 2);
			print_error_idf(s);
			return (1);
		}
	}
	return (0);
}

void	del_env_maillon(t_env *ptr, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (ptr == tmp)
		*env = (*env)->next;
	else
		while (tmp->next != ptr)
			tmp = tmp->next;
	tmp->next = ptr->next;
	ptr->next = NULL;
	free(ptr->name);
	free(ptr->var);
	free(ptr);
}
