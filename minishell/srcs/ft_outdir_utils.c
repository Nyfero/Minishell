/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outdir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:15:05 by gsap              #+#    #+#             */
/*   Updated: 2022/03/16 18:15:16 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choice_outdir(int compt, t_dir **out, char *cmd, int i)
{
	if (compt == 1 && bool_not_in_quotes(&cmd[i]))
		create_out_list(out, cmd, i, 1);
	else if (compt == 2 && bool_not_in_quotes(&cmd[i]))
		create_out_list(out, cmd, i, 2);
}

int	close_last_fd(t_dir **out)
{
	t_dir	*ptr;

	ptr = go_to_last(out);
	close(ptr->fd);
	return (1);
}
