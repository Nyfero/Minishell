/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:46:09 by gsap              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/08 15:31:47 by gsap             ###   ########.fr       */
=======
/*   Updated: 2021/08/18 12:35:50 by gsap             ###   ########.fr       */
>>>>>>> 286cb872cfc2b3b31a644ab29eb7a7de39c6955e
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	i;

<<<<<<< HEAD
	dest = ft_calloc(sizeof(char), ft_strlen(s1) + 1);
=======
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
>>>>>>> 286cb872cfc2b3b31a644ab29eb7a7de39c6955e
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
