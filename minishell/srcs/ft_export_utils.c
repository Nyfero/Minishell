/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:01:59 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 17:31:57 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_export(char *str)
{
	int		i;

	i = -1;
	if (!ft_isalpha(str[0]) && str[0] != '#')
	{
		ft_putstr_fd("export: \'", 2);
		print_error_idf(str);
		return (1);
	}
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '=')
		{
			ft_putstr_fd("export: \'", 2);
			print_error_idf(str);
			return (1);
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

void	print_flag_0(t_env *ptr, t_line *line)
{
	ft_putstr_fd("=\"", line->outdir);
	if (ptr->var)
		ft_putstr_fd(ptr->var, line->outdir);
	ft_putstr_fd("\"", line->outdir);
}

int	mod_pwd_custom(t_env *tmp)
{
	char	*var;

	var = ft_strdup(tmp->var);
	tmp = mod_env_maillon(var, tmp, tmp->flags - 2);
	free(var);
	return (0);
}
