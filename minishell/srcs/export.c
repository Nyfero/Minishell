/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:41:33 by gsap              #+#    #+#             */
/*   Updated: 2022/03/20 16:31:43 by gsap             ###   ########.fr       */
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
			if (ptr->flags < 2)
			{
				ft_putstr_fd("export ", line->outdir);
				ft_putstr_fd(ptr->name, line->outdir);
				if (ptr->flags == 0)
					print_flag_0(ptr, line);
				ft_putstr_fd("\n", line->outdir);
			}
			ptr = ptr->next;
		}
		ft_free_ls(str);
		return (0);
	}
	return (ft_export_arg(str, env));
}

int	ft_export_arg(char **str, t_env **env)
{
	int		i;
	int		tmp;
	int		ret;

	i = 0;
	ret = 0;
	tmp = 0;
	if (!*env)
		tmp = export_create_env(str[++i], env);
	if (tmp)
		ret = tmp;
	while (str[++i])
	{
		tmp = export_replace_or_create(str[i], env);
		if (tmp && !ret)
			ret = tmp;
	}
	ft_free_ls(str);
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

int	export_replace_or_create(char *str, t_env **env)
{
	t_env	*tmp;
	t_env	*ptr;
	char	*useless;

	ptr = *env;
	while (ptr->next)
		ptr = ptr->next;
	if (check_valid_export(str) == 0)
	{
		if (format_key_value(str) == 0)
			return (export_format_key_value(str, env, ptr));
		else
		{
			tmp = ft_get_var(str, *env);
			if (!tmp)
				ptr->next = create_env_maillon(str, 1);
			else if (tmp->flags >= 2)
			{
				useless = ft_strdup(tmp->var);
				tmp = mod_env_maillon(useless, tmp, tmp->flags - 2);
				free(useless);
				return (0);
			}
			if (!ptr->next)
				return (1);
		}
		return (0);
	}
	return (1);
}

int	export_format_key_value(char *str, t_env **env, t_env *ptr)
{
	char	**var;
	t_env	*tmp;

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
		tmp = mod_env_maillon(var[1], tmp, 0);
		if (!tmp)
			return (1);
	}
	ft_free_ls(var);
	return (0);
}
