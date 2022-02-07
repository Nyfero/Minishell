/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:11 by gsap              #+#    #+#             */
/*   Updated: 2022/02/07 17:44:13 by jgourlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/inc/libft.h"

// stock une commande et pointe sur la commande suivante
typedef struct s_exec
{
	char			*infile;
	char			*outfile;
	char			*cmd;
	int				indir;
	int				outdir;
	char			**env;
	struct s_exec	*next;
}	t_exec;

typedef struct s_line
{
	struct s_exec	*exec;
	struct s_line	*next;
}	t_line;

typedef struct s_env
{
	char			*name;
	char			*var;
	int				flags;
	struct s_env	*next;
}	t_env;
/*
**	flags:
**	0 affichage env, export et echo
**	1 affichage export et echo
**	2 affichage echo
*/

//	ft_error.c
int		ft_error(char *err);

//	ft_list.c
void	minishell_addlist(t_line *list, char *inpt);
t_line	*minishell_create_list(char *inpt);
t_line	*set_list_null(t_line *list);
void	minishell_del_list(t_line *line);

//	ft_parsing.c
t_line	**parsing(char *inpt);
int		check_builtin(char *str, t_env **env);
int		not_in_quotes(char const *s);

//	ft_split_minishell.c
char	**ft_split_minishell(char const *s, char c);

//	handle_signal.c
void	init_signal(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

/********************************/
/*---------BUILTIN--------------*/
/********************************/

//	echo.c
int		ft_echo(char **str);

//	pwd.c
int		ft_pwd(void);

//	ft_export.c
int		ft_export(char **str, t_env **env);
void	ft_export_no_arg(t_env **env);
int		ft_export_arg(char **str, t_env **env);
void	export_replace_or_create(char *str, t_env **env, t_env *ptr);

//	ft_export_utils.c
int		check_valid_export(char *str);
int		format_key_value(char *str);

//	ft_unset.c
int		ft_unset(char **str, t_env **env);
void	del_env_maillon(t_env *ptr, t_env **env);

//	ft_env.c
int		ft_env(char **str, t_env **env);
int		ft_env_arg(char **str);

//	ft_env_func.c
void	init_env(t_env **env, char **envp);
t_env	*create_env_maillon(char *str, int flags);
t_env	*mod_env_maillon(char *str, t_env *ptr, int flags);

//	cd.c
int		ft_cd(char **str, t_env **env);
t_env	*ft_get_var(char *search, t_env *env);

#endif
