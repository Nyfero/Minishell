/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:11 by gsap              #+#    #+#             */
/*   Updated: 2022/03/08 17:36:15 by gsap             ###   ########.fr       */
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
# define WR_IDF ": not a valid identifier"
# define OLDPWD_UNSET "OLDPWD not set"

// stock une commande et pointe sur la commande suivante
typedef struct s_line
{
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

typedef struct s_pipe
{
	char	*path_res;
	char	**path;
	char	**cmd_treat;
	int		in;
	int		out;
}	t_pipe;

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

typedef struct s_dir
{
	int				pos;
	int				len_lim;
	int				fd;
	struct s_dir	*next;
}	t_dir;

//	ft_error.c
int		ft_error(char *err);
void	print_error_wrpath(char *s);
void	print_error_idf(char *s);

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
t_dir	*go_to_last(t_dir **list);

/********************************/
/*---------PARSING--------------*/
/********************************/

//	ft_parsing.c
void	parsing(t_env **env, t_line **line, char const *inpt);
int		check_builtin(t_line *line, t_env **env);

//	ft_line_func.c
void	create_list_line(t_line **line, int len, t_env **env);
t_line	*create_line(t_env **env);
int		put_env_on_line(t_env **env, t_line *line);
void	fill_line(char *cmd, t_line *ptr, char *expand);
void	destroy_list_line(t_line **line);

//	ft_limiteur.c
char	*grep_indir(char const *str);
char	*get_limiteur(const char *str);
char	*error_limiteur(const char str);

//	ft_here_doc.c
int		write_here_doc_on_fd(char *lim);
void	put_here_doc(t_dir **here, char *cmd);
int		create_here_list(t_dir **here, char *cmd, int i);
t_dir	*create_here_maillon(char *cmd, int i);
int		check_last_indir(char const *cmd);

//	ft_infile.c
int		put_infile(t_dir **infile, char *cmd);
int		create_infile_list(t_dir **infile, char *cmd, int i);
t_dir	*create_infile_maillon(char *cmd, int i);
int		check_infile_access(char *lim);

//	ft_outdir.c
int		put_outdir(t_dir **out, t_dir **infile, int bis, char *cmd);
int		put_outdir_upto_last_indir(t_dir **out, t_dir **infile, char *cmd);
void	create_out_list(t_dir **out, char *cmd, int i, int flag);
t_dir	*create_out_maillon(char *cmd, int i, int flag);

//	ft_expand.c
char	*ft_expand(char const *inpt, t_env **env);
char	*ft_expand_utils(char *dup, int j, t_env **env);

//	ft_del_redir.c
char	*ft_remove_redir(char *expand);
char	*remove_here(char *expand);
char	*remove_infile(char *expand);
char	*remove_out(char *expand);

/********************************/
/*---------BUILTIN--------------*/
/********************************/

//	echo.c
int		ft_echo(char **str, t_line *line);

//	exit.c
int		ft_exit(char **tmp);

//	pwd.c
int		ft_pwd(t_line *line);

//	export.c
int		ft_export(char **str, t_env **env, t_line *line);
int		ft_export_arg(char **str, t_env **env);
int		export_create_env(char *str, t_env **env);
int		export_replace_or_create(char *str, t_env **env);
int		export_format_key_value(char *str, t_env **env, t_env *ptr);

//	ft_export_utils.c
int		check_valid_export(char *str);
int		format_key_value(char *str);

//	unset.c
int		ft_unset(char **str, t_env **env);
int		check_meta(char *s);
int		check_token(char *s);
void	del_env_maillon(t_env *ptr, t_env **env);

//	env.c
int		ft_env(char **str, t_env **env, t_line *line);
int		ft_env_arg(char **str, t_line *line);
char	**env_to_str(t_env **env);

//	ft_env_func.c
int		init_env(t_env **env, char **envp);
t_env	*create_env_maillon(char *str, int flags);
t_env	*mod_env_maillon(char *str, t_env *ptr, int flags);
void	destroy_env(t_env **env);
t_env	*ft_get_var(char *search, t_env *env);

//	cd.c
int		ft_cd(char **str, t_env **env);

/********************************/
/*------------EXEC--------------*/
/********************************/

//	pipex_child.c
void	ft_pipex_child(t_line *arg, int *fd, int fd_in, t_pipe data);

//	pipex_main.c
int		pipex_entry(t_line *arg, t_env **env);

// pipex_tools.c
int		ft_pipex_clean(t_line **arg, t_pipe *data, int *fd, int fd_in);
int		ft_pipex_close(int *fd, int fd_in, t_pipe *data);

#endif
