/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:16:57 by jgourlin          #+#    #+#             */
/*   Updated: 2022/03/26 18:04:39 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_free_return(t_line *arg, int ret)
{
	destroy_list_line(&arg);
	return (ret);
}

t_env	*ft_cpy_env_2(t_env *origin)
{
	t_env	*new;

	new = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = ft_strdup(origin->name);
	if (!new->name)
		return (0);
	new->var = 0;
	if (origin->var)
	{
		new->var = ft_strdup(origin->var);
		if (!new->var)
			return (0);
	}
	new->flags = origin->flags;
	new->next = 0;
	if (origin->next)
	{
		new->next = ft_cpy_env_2(origin->next);
		if (!new->next)
			return (0);
	}
	return (new);
}

int	ft_cpy_env(t_env **cpy, t_env *origin)
{
	*cpy = ft_cpy_env_2(origin);
	if (!cpy)
		return (1);
	return (0);
}

int	ft_pipex_close(int *fd, int fd_in, t_pipe *data)
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
	if (fd_in > 0)
		close(fd_in);
	if (data)
	{
		if (data->in > 2)
			close(data->in);
		if (data->out > 2)
			close(data->out);
	}
	return (1);
}

void	ft_pipex_clean(t_line **arg, t_pipe *data, int *fd, int fd_in)
{
	int	i;

	ft_pipex_close(fd, fd_in, data);
	i = 0;
	if (data->path_res)
		free(data->path_res);
	if (data->path)
	{
		while (data->path[i])
			free(data->path[i++]);
		free(data->path);
	}
	i = 0;
	if (data->cmd_treat)
	{
		while (data->cmd_treat[i])
			free(data->cmd_treat[i++]);
		free(data->cmd_treat);
	}
	if (data->env)
		destroy_env(&data->env);
	if (data->real_env)
		destroy_env(&data->real_env);
	if (arg)
		destroy_list_line(arg);
}
