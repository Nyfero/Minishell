/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:48:50 by jgourlin          #+#    #+#             */
/*   Updated: 2022/02/09 15:31:51 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	ft_file_access(char	*str)
{
	if (!str || access(str, F_OK) == -1)
		return (0);
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
