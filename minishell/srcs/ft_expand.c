/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:12:42 by gsap              #+#    #+#             */
/*   Updated: 2022/03/16 11:09:14 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char const *inpt, t_env **env)
{
	char	**dup;
	char	*expand;
	int		i;

	dup = ft_split_minishell(inpt, ' ');
	i = -1;
	expand = NULL;
	while (dup[++i])
	{
		dup[i] = ft_expand_var(dup[i], env);
		if (i > 0)
		{
			expand = ft_strjoin_and_free_s1(expand, " ");
			expand = ft_strjoin_and_free_s1(expand, dup[i]);
		}
		else
			expand = ft_strdup(dup[i]);
	}
	if (dup)
		ft_free_ls(dup);
	return (expand);
}

char	*ft_expand_var(char *dup, t_env **env)
{
	char	*tmp;
	int		i;

	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '$' && dup[i + 1])
		{
			if (bool_not_in_quotes(&dup[i]))
				tmp = expand_no_quotes(dup, env);
			else
				tmp = expand_with_quotes(dup, env);
			return (tmp);
		}
	}
	return (dup);
}

char	*expand_no_quotes(char *dup, t_env **env)
{
	t_env	*ptr;
	char	*tmp;

	ptr = check_good_expand(dup, env);
	if (ptr)
	{
		tmp = ft_substr(dup, 0, get_dolls(dup));
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = ft_substr(dup, 0, get_dolls(dup));
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

char	*expand_with_quotes(char *dup, t_env **env)
{
	char	*tmp;
	t_env	*ptr;

	if (dup[0] == '\'')
		return (del_simple(dup));
	tmp = del_quotes(dup);
	printf("tmp:%s\n", tmp);
	ptr = check_good_expand(del_quotes(tmp), env);
	if (ptr)
	{
		tmp = ft_substr(dup, 0, get_dolls(tmp));
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
		if (!tmp)
			return (NULL);
		}
	else
	{
		tmp = ft_substr(dup, 0, get_dolls(tmp));
		if (!tmp)
			return (NULL);
	}
	return (tmp);
/*
	int	i = 1;
	int j = 1;
	tmp = NULL;
	res = NULL;
	printf("alpha 1\ndup=%s\n", dup);
	res = ft_strdup("");
	while (dup[i] && dup[i] != '\"')
	{
		printf("alpha 2\n");
		if (dup[i] == '$')
		{
			printf("alpha 3 i=%02d\n",i);//suppr
			printf("i=%d j=%d", i, j);//suppr
			if (i != j)
			{
				tmp = ft_substr(dup, j, i - 1);
				res = ft_strjoin_and_free_all(res, tmp);
				printf("test_0 = |%s|\n", res);//suppr
			}


			tmp = jgourlin(dup + i, env, &i);
			res = ft_strjoin_and_free_s1(res, tmp);
			printf("i=(%02d)test_1 = %s\n", i, res);//suppr

			j = i;
		}
		i++;
	}
	printf("alpha 4`\n");
	printf("fianl=|%s|\n", res);*/
}

t_env	*check_good_expand(char *str, t_env **env)
{
	char	*tmp;
	t_env	*ptr;

	tmp = ft_strdup(&str[get_dolls(str) + 1]);
	if (!tmp)
		return (NULL);
	printf("str:%s\n", tmp);
	ptr = ft_get_var(tmp, *env);
	free(tmp);
	return (ptr);
}
