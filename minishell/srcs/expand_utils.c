/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:03 by gsap              #+#    #+#             */
/*   Updated: 2022/03/21 19:21:59 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

t_env	*check_good_expand(char *str, t_env **env)
{
	int		i;
	t_env	*ptr;
	char	*bis;

	i = 1;
	if (!str[i])
	{
		ptr = ft_get_var("!", *env);
		return (ptr);
	}
	if (str[i] == '?')
		return (ft_get_var("?", *env));
	while (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	bis = ft_substr(str, 1, i - 1);
	if (!bis)
		return (NULL);
	ptr = ft_get_var(bis, *env);
	free(bis);
	return (ptr);
}

int	len_name(char *str)
{
	int	i;

	i = 1;
	while (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*replace_dolls(char *str, char *before, int i)
{
	int		compt;
	char	*after;

	compt = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			compt++;
		else
			break ;
	}
	after = ft_substr(str, i, ft_strlen(str));
	if (!after)
		after = ft_strdup("");
	free(str);
	if (compt % 2)
		str = ft_strjoin_and_free_s1(before, "");
	else
		str = ft_strjoin_and_free_s1(before, "$");
	return (ft_strjoin_and_free_all(str, after));
}
