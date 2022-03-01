/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:01:59 by gsap              #+#    #+#             */
/*   Updated: 2022/02/28 10:44:52 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_export(char *str)
{
	int		i;

	i = -1;
	if (ft_isdigit(str[0]) || str[0] == '=')
	{
		printf("export: '%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '=')
		{
			if (i == 0 && str[i] == '#')
				;
			else
			{
				printf("export: '%s': not a valid identifier\n", str);
				return (1);
			}
		}
	}
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
