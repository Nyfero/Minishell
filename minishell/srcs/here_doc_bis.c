/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:15:01 by gsap              #+#    #+#             */
/*   Updated: 2022/03/01 15:50:50 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int here_doc(char const *s)
{
	int fd[2];
	int id;
	int	x;
	int	y;

	if (pipe(fd) == -1)
	{
		printf("An error ocurred with opening the pipe\n");
		return (1);
	}
	id = fork();
	if (id == -1)
	{
		printf("An error ocurred with fork\n");
		return (2);
	}
	if (id == 0) // child process
	{s
		close(fd[0]);
		if (write(fd[1], &s, ft_strlen(s)) == -1)
		{
			printf("An error ocurred with writing to the pipe\n");
			return (3);
		}
		close(fd[1]);
	}
	else
	{
		// Parent process
		close(fd[1]);
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("An error ocurred with reading from the pipe\n");
			return (4);
		}
		printf("Got from child process %d\n", y);
		y = y * 3;
		printf("Result is %d\n", y);
		close(fd[0]);
	}
	return (0);
}
