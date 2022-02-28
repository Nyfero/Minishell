/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:29:02 by gsap              #+#    #+#             */
/*   Updated: 2022/02/28 15:08:07 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_nbr_pipe(char **cmd, char const *inpt)
{
	int	compt;
	int	i;

	i = 0;
	compt = 0;
	while (inpt[i])
	{
		if (inpt[i] && (inpt[i] == '|') && not_in_quotes(inpt))
		{
			i++;
			compt++;
		}
		while (inpt[i] && (inpt[i] != '|'))
			i++;
	}
	if (compt != ft_lstrlen(cmd) - 1)
		return (1);
	return (0);
}

static int	check_pipe(char **cmd, char const *inpt)
{
	int	i;
	int	j;
	int	compt;

	if (check_nbr_pipe(cmd, inpt))
		return (1);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		compt = 0;
		while(cmd[i][++j])
		{
			if (!ft_isalnum(cmd[i][j]))
				compt++;
		}
		if ((size_t)compt == ft_strlen(cmd[i]))
			return (1);
	}
	return (0);
}

void	parsing(t_line **line, char const *inpt)
{
	char	**cmd;
	t_line	*ptr;
	int		i;
	//char	*expand;

	if (!inpt)
		return ;
	cmd = ft_split_minishell(inpt, '|');
	if (check_pipe(cmd, inpt))
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return ;
	}
	create_list_line(line, ft_lstrlen(cmd));
	ptr = *line;
	i = 0;
	while (ptr != NULL)
	{
		fill_line(cmd[i], ptr);
		i++;
		ptr = ptr->next;
	}
	ft_free_ls(cmd);
		return;
	/*expand = handle_here_doc(inpt);
	printf("expand =>%s\n", expand);
	if (!expand)
		return ;
	write(1, "1\n", 2);
	expand = ft_expand(expand, env);
	printf("expand =>%s\n", expand);
	write(1, "2\n", 2);
	if (!expand)
		return ;
	printf("%d\n", ft_lstrlen(tmp));
	write(1, "3\n", 2);
	write(1, "4\n", 2);
	//expand $
	//check outdir
	//check indir*/
}

/*
**	A mettre au propre
*/

char	*ft_expand(char const *inpt, t_env ** env)
{
	char	**dup;
	char	*tmp;
	char	*expand;
	t_env	*ptr;
	int		i;
	int		j;

	dup = ft_split_minishell(inpt, ' ');
	i = -1;
	expand = NULL;
	while (dup[++i])
	{
		j = -1;
		while (++j < 3)
		{
			if (dup[i][j] == '$')
			{
				if (dup[i][j + 1] && dup[i][1] != '<' && dup[i][j + 1] != '$')
				{
					ptr = ft_get_var(&dup[i][j + 1], *env);
					if (ptr)
					{
						tmp = ft_substr(dup[i], 0, j);
						tmp = ft_strjoin_and_free_s1(tmp, ptr->var);
						free(dup[i]);
						dup[i] = tmp;
					}
					else
					{
						tmp = ft_substr(dup[i], 0, j);
						free(dup[i]);
						dup[i] = tmp;
					}
				}
			}
		}
		if (i > 0)
		{
			expand = ft_strjoin_and_free_s1(expand, " ");
			expand = ft_strjoin_and_free_all(expand, dup[i]);
		}
		else
			expand = ft_strdup(dup[i]);
	}
	return (expand);
}

/*void	infile_parsing(char *inpt, t_line *line)
{
	int		i;

	i = 0;
	while (inpt[i + 1])
	{
		if (inpt[i] == '<' && inpt[i + 1] == '<')
		{
			i++;
			parsing_double_indir(&inpt[i + 1], line);
		}
		else if (inpt[i] == '<')
			parsing_simple_indir(&inpt[i + 1], line);
		i++;
	}
}

void	outfile_parsing(char *inpt, t_line	*line)
{
	int		i;

	i = 0;
	while (inpt[i + 1])
	{
		if (inpt[i] == '>' && inpt[i + 1] == '>')
		{
			i++;
			parsing_double_outdir(&inpt[i + 1], line);
		}
		else if (inpt[i] == '>')
			parsing_simple_outdir(&inpt[i + 1], line);
		i++;
	}
}*/

int	check_builtin(char *str, t_env **env)
{
	char	**tmp;
	int		ret;

	ret = 0;
	tmp = ft_split_minishell(str, ' ');
	for (int i = 0; tmp[i]; i++)
		printf("tmp[%d] =>%s\n", i, tmp[i]);
	if (ft_strncmp(tmp[0], "env", 4) == 0)
		return (ft_env(tmp, env));
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		return (ft_unset(tmp, env));
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		return (ft_export(tmp, env));
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		return (ft_cd(tmp, env));
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
	{
		ft_free_ls(tmp);
		return (-1);
	}
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(tmp[0], "echo", 5) == 0)
		return (ft_echo(tmp));
	ft_free_ls(tmp);
	return (-5);
}


int	not_in_quotes(char const *s)
{
	int	s_qt;
	int	d_qt;

	s_qt = 0;
	d_qt = 0;
	while (*s)
	{
		if (*s == 39)
			s_qt++;
		if (*s == 34)
			d_qt++;
		s++;
	}
	if (s_qt % 2 == 0 && d_qt % 2 == 0)
		return (1);
	return (0);
}
