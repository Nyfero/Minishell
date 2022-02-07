/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:41:33 by gsap              #+#    #+#             */
/*   Updated: 2022/02/07 10:58:20 by gsap             ###   ########.fr       */
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
		while (str[i])
		{
			if (check_valid_export(str[i], env) == 0)
			{
				if (format_key_value(str[i]) == 0)
					ptr->next = create_env_maillon(str[i], 0);
				else
					ptr->next = create_env_maillon(str[i], 1);
				ptr = ptr->next;
			}
			//message d'erreur en fonction de l'arg (soit invalide soit --)
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

int	check_valid_export(char *str, t_env **env)
{
	//t_env	*ptr;
	int		i;
	(void)env;

	i = -1;
	if (ft_isdigit(str[0]) || str[0] == '=')
	{
		printf("export: '%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[++i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '=')
		{
			printf("export: '%s': not a valid identifier\n", str);
			return (1);
		}
	}
	/*while (ptr)
	{
		if (ft_strncmp(str, ptr->name, ft_strlen))
	}*/
	return (0);
}

int	format_key_value(char *str)
{
	int	i;
	int	compt;

	i = -1;
	compt = 1;
	while (str[++i])
		if (str[i] == '=')
			compt = 0;
	return (compt);
}
