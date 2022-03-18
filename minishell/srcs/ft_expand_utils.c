/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:03 by gsap              #+#    #+#             */
/*   Updated: 2022/03/18 18:33:06 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*check_good_expand(char *str, t_env **env)
{
	int		i;
	t_env	*ptr;
	char	*bis;

	i = 1;
	if (!str[i])
	{
		ptr = ft_get_var("!", *env);
		if (!ptr)
			ptr = create_env_maillon("!=$", 10);
		return (ptr);
	}
	while (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	bis = ft_substr(str, 1, i - 1);
	if (!bis)
		return (NULL);
	ptr = ft_get_var(bis, *env);
	free(bis);
	return (ptr);
}
