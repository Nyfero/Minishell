/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free_all.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:29:50 by gsap              #+#    #+#             */
/*   Updated: 2022/03/26 18:06:09 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*check_who_is_not_null(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

char	*ft_strjoin_and_free_all(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*strcopie;

	if (!s1 || !s2)
		return (check_who_is_not_null(s1, s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	strcopie = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!strcopie)
		return (check_who_is_not_null(s1, s2));
	i = -1;
	while (++i < len_s1)
		strcopie[i] = s1[i];
	while ((i - len_s1) < len_s2)
	{
		strcopie[i] = s2[(i - len_s1)];
		i++;
	}
	strcopie[i] = 0;
	check_who_is_not_NULL(s1, s2);
	return (strcopie);
}
