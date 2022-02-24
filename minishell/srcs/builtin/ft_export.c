/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:41:33 by gsap              #+#    #+#             */
/*   Updated: 2022/02/24 17:46:50 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**	Valeurs de retour de export:
**	0 tout c'est bien passé
**	1 not a valid identifier
**	2 bad flags ou syntax error near
*/

int	ft_export(char **str, t_env **env)
{
	if (!*env)
		return (1);
	if (!str[1])
		ft_export_no_arg(env);
	else
		return (ft_export_arg(str, env));
	return (0);
}

void	ft_export_no_arg(t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ptr->flags == 0)
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->var);
		else if (ptr->flags == 1)
			printf("declare -x %s\n", ptr->name);
		ptr = ptr->next;
	}
	return ;
}

int	ft_export_arg(char **str, t_env **env)
{
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = *env;
	while (ptr->next)
		ptr = ptr->next;
	while (str[++i])
	{
		printf("str=%s\n", str[i]);
		export_replace_or_create(str[i], env, ptr);
	}
	return (0);
}

void	export_replace_or_create(char *str, t_env **env, t_env *ptr)
{
	char	**ls;
	t_env	*tmp;

	if (check_valid_export(str) == 0)
	{
		if (format_key_value(str) == 0)
		{
			ls = ft_split_minishell(str, '=');
			tmp = ft_get_var(ls[0], *env);
			if (tmp == 0)
				ptr->next = create_env_maillon(str, 0);
			else
				tmp = mod_env_maillon(str, tmp, 0);
			ft_free_ls(ls);
		}
		else
		{
			tmp = ft_get_var(str, *env);
			if (tmp == 0)
				ptr->next = create_env_maillon(str, 1);
		}
		ptr = ptr->next;
	}
}
