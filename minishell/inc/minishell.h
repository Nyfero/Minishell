/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:11 by gsap              #+#    #+#             */
/*   Updated: 2022/03/01 11:50:39 by gsap             ###   ########.fr       */
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

//	message d'erreur
# define WR_PATH ": No such file or directory"
# define OLDPWD_UNSET "OLDPWD not set"

# define TRUE 1
# define FALSE 0

// stock une commande et pointe sur la commande suivante
typedef struct s_line
{
	char			*infile;
	char			*outfile;
	char			*cmd;
	char			**env;
	char			**path;
	int				indir;
	int				outdir;
	struct s_line	*next;
}	t_line;
/*
**	indir flags:
**	0 no < or <<
**	1 = <
**	2 = <<
**	outdir same things
*/

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

//	ft_split_minishell.c
char	**ft_split_minishell(char const *s, char c);

//	handle_signal.c
void	init_signal(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

//	ft_tools.c
int		ft_dir_access(char *str);
int		ft_file_access(char	*str);
int		not_in_quotes(char const *s);

/********************************/
/*---------PARSING--------------*/
/********************************/

//	ft_line_func.c
void	create_list_line(t_line **line, int len, t_env **env);
t_line	*create_line(t_env **env);
void	fill_line(char *cmd, t_line *ptr);
void	destroy_list_line(t_line** line);

//	ft_here_doc.c
char	*handle_here_doc(char const *str);
char	*replace_here_doc(char *dup, int i);
char	*read_here_doc(char *lim);
int		check_here_doc(char *dup, int i);
char	*get_limiteur(const char *str);

//	ft_parsing.c
void	parsing(t_env **env, t_line **line, char const *inpt);
int		check_builtin(char *str, t_env **env);

//	ft_expand.c
char	*ft_expand(char const *inpt, t_env ** env);
char	*ft_expand_utils(char *dup, int j, t_env **env);

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
char	**env_to_str(t_env **env);

//	ft_env_func.c
void	init_env(t_env **env, char **envp);
t_env	*create_env_maillon(char *str, int flags);
t_env	*mod_env_maillon(char *str, t_env *ptr, int flags);
void	destroy_env(t_env **env);
t_env	*ft_get_var(char *search, t_env *env);

//	cd.c
int		ft_cd(char **str, t_env **env);

//	pipex_child.c
void	ft_pipex_child(t_line *arg, int *fd, int fd_in, char **path);

//	pipex_main.c
int	pipex_entry(t_line *arg, t_env **env);

#endif
