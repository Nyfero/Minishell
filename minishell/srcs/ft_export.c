/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:41:33 by gsap              #+#    #+#             */
/*   Updated: 2022/03/07 14:14:54 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Valeurs de retour de export:
**	0 tout c'est bien passé
**	1 not a valid identifier
**	2 bad flags ou syntax error near
*/

int	ft_export(char **str, t_env **env, t_line *line)
{
	t_env	*ptr;

	if (!env)
		return (1);
	ptr = *env;
	if (!str[1])
	{
		while (ptr)
		{
			ft_putstr_fd("declare -x ", line->outdir);
			ft_putstr_fd(ptr->name, line->outdir);
			if (ptr->flags == 0)
			{
				ft_putstr_fd("=\"", line->outdir);
				ft_putstr_fd(ptr->var, line->outdir);
				ft_putstr_fd("\"", line->outdir);
			}
			ft_putstr_fd("\n", line->outdir);
			ptr = ptr->next;
		}
		return (0);
	}
	return (ft_export_arg(str, env));
}

int	ft_export_arg(char **str, t_env **env)
{
	t_env	*ptr;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	ptr = NULL;
	if (!*env)
		ret = export_create_env(str[++i], env);
	while (str[++i])
	{
		ptr = *env;
		while (ptr->next)
			ptr = ptr->next;
		ret = export_replace_or_create(str[i], env, ptr);
	}
	return (ret);
}

int	export_create_env(char *str, t_env **env)
{
	if (check_valid_export(str) == 0)
	{
		if (format_key_value(str) == 0)
			*env = create_env_maillon(str, 0);
		else
			*env = create_env_maillon(str, 1);
		if (!*env)
			return (1);
		return (0);
	}
	return (1);
}

int	export_replace_or_create(char *str, t_env **env, t_env *ptr)
{
	char	**var;
	t_env	*tmp;

	if (check_valid_export(str) == 0)
	{
		if (format_key_value(str) == 0)
		{
			var = ft_split_minishell(str, '=');
			tmp = ft_get_var(var[0], *env);
			if (!tmp)
			{
				ptr->next = create_env_maillon(str, 0);
				if (!ptr->next)
					return (1);
			}
			else
			{
				tmp = mod_env_maillon(str, tmp, 0);
				if (!tmp)
					return (1);
			}
			ft_free_ls(var);
		}
		else
		{
			tmp = ft_get_var(str, *env);
			if (!tmp)
				ptr->next = create_env_maillon(str, 1);
			if (!ptr->next)
				return (1);
		}
		return (0);
	}
	return (1);
}
