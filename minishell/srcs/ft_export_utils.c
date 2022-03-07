/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:01:59 by gsap              #+#    #+#             */
/*   Updated: 2022/03/07 12:44:46 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_export(char *str)
{
	int		i;

	i = -1;
	{
		if ((check_meta(str) || str[0] == '=') && str[0] != '#')
		{
			ft_putstr_fd("export: \'", 2);
			print_error_idf(str);
			return (1);
		}
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
