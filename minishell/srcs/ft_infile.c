/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:01:52 by gsap              #+#    #+#             */
/*   Updated: 2022/03/14 08:50:50 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Créer et stocke mes infiles. Si une erreur apparait, renvoie 1 sinon renvoie 0
*/

int	put_infile(t_dir **infile, char *cmd)
{
	int		i;
	int		compt;

	i = -1;
	while (cmd[++i])
	{
		compt = 0;
		while (cmd[i] == '<' && bool_not_in_quotes(&cmd[i]))
		{
			i++;
			compt++;
		}
		if (compt == 1)
		{
			compt = create_infile_list(infile, cmd, i);
			if (compt)
				return (compt);
		}
	}
	return (0);
}

int	create_infile_list(t_dir **infile, char *cmd, int i)
{
	t_dir	*ptr;

	if (!*infile)
	{
		*infile = create_infile_maillon(cmd, i);
		if (!*infile)
			return (1);
		if ((*infile)->fd == -1)
			return (2);
	}
	else
	{
		ptr = go_to_last(infile);
		close(ptr->fd);
		ptr->next = create_infile_maillon(cmd, i);
		if (!ptr->next)
			return (1);
		if (ptr->next->fd == -1)
			return (2);
	}
	return (0);
}

t_dir	*create_infile_maillon(char *cmd, int i)
{
	char	*lim;
	t_dir	*tmp;

	tmp = ft_calloc(sizeof(t_dir), 1);
	if (!tmp)
		return (NULL);
	tmp->pos = i - 1;
	tmp->fd = -1;
	tmp->next = NULL;
	lim = get_limiteur(&cmd[i]);
	if (!lim)
		return (tmp);
	if (check_infile_access(lim))
	{
		free(lim);
		return (tmp);
	}
	tmp->fd = open(lim, O_RDONLY);
	if (tmp->fd == -1)
		perror("open");
	free(lim);
	return (tmp);
}

int	check_infile_access(char *lim)
{
	if (ft_file_access(lim) == 0)
	{
		ft_putstr_fd(lim, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(lim);
		return (1);
	}
	if (ft_file_access(lim) == -1)
	{
		ft_putstr_fd(lim, 2);
		if (access(lim, F_OK | R_OK))
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": Is a directory\n", 2);
		free(lim);
		return (1);
	}
	return (0);
}

/*
**	Une fonction qui me dis si j'ai en dernier un here doc ou un infile
**	Renvoie 2 si here_doc, 1 si infile et 0 sinon
*/

int	check_last_indir(char const *cmd)
{
	int		i;

	i = ft_strlen(cmd) - 1;
	while (i >= 0)
	{
		if (cmd[i] == '<' && bool_not_in_quotes(&cmd[i]))
		{
			if ((i - 1) >= 0 && cmd[i - 1] == '<')
				return (2);
			return (1);
		}
		i--;
	}
	return (0);
}
