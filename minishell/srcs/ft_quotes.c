/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:13:08 by gsap              #+#    #+#             */
/*   Updated: 2022/03/17 15:57:13 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Renvoie 1 si l'élément n'est pas dans des quotes et 0 s'il y est.
*/

int	bool_not_in_quotes(char const *s)
{
	if (bool_not_in_simple(s) && bool_not_in_double(s))
		return (1);
	return (0);
}

int	bool_not_in_simple(char const *s)
{
	int	compt;
	int	i;

	compt = 0;
	i = 0;
	while(s[i])
	{
		if (s[i] == '\'')
			compt++;
		i++;
	}
	if ((compt % 2))
		return (0);
	return (1);
}

int	bool_not_in_double(char const *s)
{
	int	compt;
	int	i;

	compt = 0;
	i = 0;
	while(s[i])
	{
		if (s[i] == '\"')
			compt++;
		i++;
	}
	if ((compt % 2))
		return (0);
	return (1);
}

char	*del_simple(char *lim)
{
	char 	*tmp;
	char	*after;
	int		i;

	i = -1;
	while (lim[++i])
	{
		if (lim[i] == '\'' && bool_not_in_double(&lim[i]))
		{
			tmp = ft_substr(lim, 0, i);
			if (lim[i + 1])
			{
				after = ft_substr(lim, i + 1, ft_strlen(lim) - i);
				free(lim);
				lim = ft_strjoin_and_free_all(tmp, after);
			}
			else
			{
				free(lim);
				lim = ft_strdup(tmp);
				free(tmp);
			}
			if (!lim)
				return (NULL);
		}
	}
	if (!lim)
		return (NULL);
	return (lim);
}

char	*ft_jgourlin(char *str, char c)
{
	int	i;
	char	*res;

	i = 1;
	//printf("bravo 1\n");
	if (str)
		//printf("---JGOUR entry = %s\n", str);
	//if (!str)
	//	return (0);
	while (str[i] && str[i] != c)
	{
		i++;
	}
	res = malloc(sizeof(char) * (i + 1));
	i = 1;
	while (str[i] && str[i] != c)
	{
		res[i - 1] = str[i];
		i++;
	}
	res[i - 1] = 0;
	//printf("---JGOUR res = %s\n", res);
	return (res);
}

int ft_got_c(char const *s, char c)
{
//	printf("alpha 1\n");
	int	i;

	i = -1;
	//printf("alpha 2\n");
	if (s == 0)
		return (0);
	while (s[++i])
	{
		//printf("alpha 3\n");
		if (s[i] == c)
			return (1);
		//printf("alpha 4\n");
	}
//	printf("alpha 5\n");
	return (0);
}

char	*del_quotes(char *lim)
{
	char 	*tmp;
	char	*after;
	int		i;
	char	*test;

	i = 0;
	//printf("lim = %s\n", lim);
	test = 0;
	while (lim[i])
	{
		/*printf("lim[%d]:%c\n", i , lim[i]);
		printf("!in double = %d\n", bool_not_in_double(&lim[i]));
		printf("!in simple = %d\n", bool_not_in_simple(&lim[i]));
		printf("res jgourlin = %s\n", test);*/
		//if (((lim[i] == '\"' && bool_not_in_simple(&lim[i])) || (lim[i] == '\"' && !bool_not_in_simple(&lim[i]) && !bool_not_in_double(test)))
		//	|| ((lim[i] == '\'' && bool_not_in_double(&lim[i])) || (lim[i] == '\'' && !bool_not_in_double(&lim[i]) && !bool_not_in_simple(test))))
		if (((lim[i] == '\"' && bool_not_in_simple(&lim[i])) || (lim[i] == '\"' && !bool_not_in_simple(&lim[i]) && !ft_got_c(test, '\"')))
			|| ((lim[i] == '\'' && bool_not_in_double(&lim[i])) || (lim[i] == '\'' && !bool_not_in_double(&lim[i]) && !ft_got_c(test, '\''))))
		{
			//test = lim + i;
			test = ft_jgourlin(lim + i, lim[i]);
			tmp = ft_substr(lim, 0, i);
			//printf("tmp:%s\n", tmp);
			if (lim[i + 1])
			{
				after = ft_substr(lim, i + 1, ft_strlen(lim));
			//	printf("after:%s\n", after);
				free(lim);
				lim = ft_strjoin_and_free_all(tmp, after);
			}
			else
			{
				free(lim);
				lim = ft_strdup(tmp);
				free(tmp);
			}
			if (!lim)
				return (NULL);
			//printf("lim:%s\n\n", lim);
		}
		else
			i++;
	}
	if (!lim)
		return (NULL);
	return (lim);
}
