/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:48:50 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/01 10:39:52 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	F_OK = fichier existe
**	X_OK= exec droit
**	W_OK= ecrituredroit
**	R_OK= lecture droit
*/

/*
** errno == 13 -> pas acces aux droits
** errno == 20 -> pas un dossier
*/

int	ft_dir_access(char *str)
{
	DIR*	fd;

	fd = opendir(str);
	if (fd || errno == 13)
	{
		if (fd)
			closedir(fd);
		return (-1);
	}
	return (0);
}

int	ft_file_access(char	*str)
{
	if (ft_dir_access(str) == -1)
		return (-1);
	if (!access(str, F_OK | R_OK | W_OK | X_OK))
		return (8);
	else if (!access(str, F_OK | R_OK | W_OK))
		return (7);
	else if (!access(str, F_OK | R_OK | X_OK))
		return (6);
	else if (!access(str, F_OK | R_OK))
		return (5);
	else if (!access(str, F_OK | W_OK | X_OK))
		return (4);
	else if (!access(str, F_OK | W_OK))
		return (3);
	else if (!access(str, F_OK | X_OK))
		return (2);
	else if (!access(str, F_OK))
		return (1);
	return (0);
}

int	not_in_quotes(char const *s)
{
	int	s_qt;
	int	d_qt;

	s_qt = 0;
	d_qt = 0;
	while (*s)
	{
		if (*s == 39)
			s_qt++;
		if (*s == 34)
			d_qt++;
		s++;
	}
	if (s_qt % 2 == 0 && d_qt % 2 == 0)
		return (1);
	return (0);
}
