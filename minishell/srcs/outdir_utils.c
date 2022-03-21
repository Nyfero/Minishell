/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outdir_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:15:05 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 19:25:45 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choice_outdir(int compt, int out, char *cmd, int i)
{
	if (compt == 1 && bool_not_in_quotes(&cmd[i]))
		return (create_out(out, cmd, i, 1));
	else if (compt == 2 && bool_not_in_quotes(&cmd[i]))
		return (create_out(out, cmd, i, 2));
	return (-1);
}

int	close_last_fd(t_dir **out)
{
	t_dir	*ptr;

	ptr = go_to_last(out);
	close(ptr->fd);
	return (1);
}
