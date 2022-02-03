/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:11 by gsap              #+#    #+#             */
/*   Updated: 2022/02/03 13:49:05 by gsap             ###   ########.fr       */
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

//	message d'erreur CD
# define WR_PATH "cd: no such file or directory: "
# define WR_ABS_PATH ":No such file or directory"
# define OLDPWD_UNSET "cd: OLDPWD not set"

//	message d'erreur


# define TRUE 1
# define FALSE 0

// stock une commande et pointe sur la commande suivante
typedef struct s_line
{
	char			*infile;
	char			*outfile;
	char			*cmd;
	int				indir;
	int				outdir;
	char			**env;
	struct s_line	*next;
}	t_line;

//structure pour stocker l'environnement
typedef struct s_env
{
	char			*name;
	char			*var;
	int				flags;
	struct s_env	*next;
}	t_env;

//	ft_unset.c
void	ft_unset(char **str, t_env **env);

//	ft_env.c
void	ft_env(t_env *env);

//	ft_env_func.c
void	init_env(t_env **env, char **envp);
void	create_env_list(t_env **env, char *str);
t_env	*create_env_maillon(char *str, int flags);

//	ft_error.c
int		ft_error(char *err);

//	ft_list.c
void	minishell_addlist(t_line **list, char *inpt);
t_line	*minishell_create_list(char *inpt);
t_line	*set_list_null(t_line *list);
void	minishell_del_list(t_line *line);

//	ft_parsing.c
t_line	*parsing(char *inpt);
int		check_builtin(char *str, t_env *env);
int		not_in_quotes(char const *s);

//	ft_split_minishell.c
char	**ft_split_minishell(char const *s, char c);

//	handle_signal.c
void	init_signal(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

//	echo.c
void	ft_echo(char **str);

//	pwd.c
void	ft_pwd(void);

#endif
