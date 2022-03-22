/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:11 by gsap              #+#    #+#             */
/*   Updated: 2022/03/22 19:06:17 by jgourlin         ###   ########.fr       */
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
	struct s_env	*real_env;
	struct s_env	*env;
	char			*path_res;
	char			**path;
	char			**cmd_treat;
	int				in;
	int				out;
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
	int				fd;
	struct s_dir	*next;
}	t_dir;

typedef struct s_garbage
{
	t_env	*env;
	char	*inpt;
	char	**cmd;
	t_line	**line;
	char	*expand;
}	t_garbage;

//	main.c
int		main(int argc, char **argv, char **envp);
void	parse_and_exec(t_env **env, t_line **line, char *inpt, t_garbage bin);
int		exit_ctr_d(t_env *env);
void	exec_line(t_line **line, t_env **env);
int		close_minishell(t_env *env, int argc, char **argv);

//	ft_error.c
int		ft_error(char *err);
void	print_error_wrpath(char *s);
void	print_error_idf(char *s);
int		print_error_syntax(int x);
void	warning_here_doc(char *s, int x);

//	ft_split_minishell.c
char	**ft_split_minishell(char const *s, char c);

//	garbage_free.c
void	reset_bin(t_garbage bin);
void	free_bin(t_garbage bin);

//	ft_sig_init.c
void	signal_main(void);
void	signal_child(void);
void	signal_here(void);

//	handle_signal.c
void	sigint_main(int sig);
void	sigint_child(int sig);
void	sigquit_main(int sig);
void	sigquit_child(int sig);

//	ft_tools.c
int		ft_dir_access(char *str);
int		ft_file_access(char	*str);
t_dir	*go_to_last(t_dir **list);
int		get_dolls(char *dup);

//	quotes_check.c
int		bool_not_in_quotes(char const *s);
int		bool_not_in_simple(char const *s);
int		bool_not_in_double(char const *s);
char	*get_words_in_quotes(char *str, char c);
int		ft_strchr_quotes(char const *s, char c);

//	quotes_del.c
char	*del_simple(char *lim);
char	*replace_lim(char *lim, char *before, int i);
char	*del_quotes(char *lim);
int		little_check(char *lim, int i, char *tmp);

/********************************/
/*---------PARSING--------------*/
/********************************/

//	ft_parsing.c
int		parsing(t_env **env, t_line **line, char const *inpt, t_garbage bin);
int		check_builtin(t_line *line, t_env **env, int x);
int		close_wrong_inpt(char **cmd, int i);
int		parse(t_env **env, t_line **line, char *inpt, t_garbage bin);
int		check_only_redir(t_line *line, t_env **env, char *inpt);

//	ft_check_pipe.c
int		check_inpt(char **cmd, char const *inpt);
int		check_pipe(char **cmd, char const *inpt);
int		check_nbr_pipe(char **cmd, char const *inpt);
int		check_quotes(char const *inpt);

//	ft_line_func.c
void	create_list_line(t_line **line, int len, t_env **env);
t_line	*create_line(t_env **env);
void	destroy_list_line(t_line **line);

//	fill_line.c
int		fill_line(char *cmd, t_line *ptr, t_env **env, t_garbage bin);
int		place_indir(char *cmd, char	*expand, t_garbage bin, t_dir **infile);
int		place_outdir(char *expand, t_dir *infile);
char	*place_cmd(char *expand);
int		close_wrong_indir(char *expand, t_dir *infile);

//	ft_limiteur.c
char	*grep_indir(char const *str);
char	*get_limiteur(const char *str);
char	*error_limiteur(const char str);

//	ft_here_doc.c
int		write_here_doc_on_fd(char *lim, t_garbage bin);
void	get_here_doc(char *lim, int fd[2]);
int		put_here_doc(char *cmd, t_garbage bin);
int		create_here(int here, char *cmd, int i, t_garbage bin);
int		close_here(int here);

//	ft_infile.c
int		put_infile(t_dir **infile, char *cmd);
int		create_infile_list(t_dir **infile, char *cmd, int i);
t_dir	*create_infile_maillon(char *cmd, int i);
int		check_infile_access(char *lim);
int		check_last_indir(char const *cmd);

//	ft_outdir.c
int		put_outdir(char *cmd);
int		put_outdir_upto_last_indir(int out, t_dir *infile, char *cmd);
int		create_out(int out, char *cmd, int i, int flag);
void	destroy_dir(t_dir **dir);

//	ft_outdir_utils.c
int		choice_outdir(int compt, int out, char *cmd, int i);
int		close_last_fd(t_dir **out);

//	ft_expand.c
char	*ft_expand(char const *inpt, t_env **env);
char	*ft_expand_var(char *dup, t_env **env);
char	*expand_no_quotes(char *dup, t_env **env);
char	*expand_with_quotes(char *dup, t_env **env);
char	*replace_expand(char *dup, int i, t_env **env);

//	ft_expand_utils.c
t_env	*check_good_expand(char *str, t_env **env);
int		len_name(char *str);
char	*replace_dolls(char *str, char *before, int i);

//	ft_del_redir.c
char	*ft_remove_redir(char *expand);
char	*remove_infile(char *expand, int i);
char	*remove_out(char *expand, int i);
char	*blank_replace(char *tmp, char *expand, int i, int compt);
int		return_compt(int compt, int i);

/********************************/
/*---------BUILTIN--------------*/
/********************************/

//	echo.c
int		ft_echo(char **str, t_line *line);

//	exit.c
int		ft_exit(char **tmp, t_env **env, t_line *line, int x);
int		ft_exit_arg(char **str, t_env **env, t_line *line, int x);
void	clean_exit_memory(char **str, t_env **env, t_line *line, int x);
void	print_error_exit(char *str);

//	pwd.c
int		ft_pwd(t_line *line, char **str);

//	export.c
int		ft_export(char **str, t_env **env, t_line *line);
int		ft_export_arg(char **str, t_env **env);
int		export_create_env(char *str, t_env **env);
int		export_replace_or_create(char *str, t_env **env);
int		export_format_key_value(char *str, t_env **env, t_env *ptr);

//	ft_export_utils.c
int		check_valid_export(char *str);
int		format_key_value(char *str);
void	print_flag_0(t_env *ptr, t_line *line);
int		mod_pwd_custom(t_env *tmp);

//	unset.c
int		ft_unset(char **str, t_env **env);
int		check_meta(char *s);
int		check_token(char *s);
void	del_env_maillon(t_env *ptr, t_env **env);

//	env.c
int		ft_env(char **str, t_env **env, t_line *line);
int		ft_env_arg(char **str, t_line *line);
char	**env_to_str(t_env **env);
t_env	*create_env_flags(char *envp, t_env **env);
t_env	*create_env_var(t_env **env);

//	ft_env_func.c
int		init_env(t_env **env, char **envp);
t_env	*create_env_maillon(char *str, int flags);
t_env	*mod_env_maillon(char *str, t_env *ptr, int flags);
void	destroy_env(t_env **env);
t_env	*ft_get_var(char *search, t_env *env);

//	cd.c
int		ft_cd(char **str, t_env **env);

//	cd_setting.c

int		ft_change_oldpwd(t_env **env);
int		ft_change_pwd(t_env **env);

//	cd_tools.c
int		ft_cd_error_char(char c);
int		ft_cd_error_double(char *s1, char *s2);
int		ft_change_oldpwd_pwd(t_env **old, int flags, char *var);
int		ft_change_oldpwd_npwd(t_env **old, int flags);
int		ft_change_oldpwd_old_exist(t_env **env);

/********************************/
/*------------EXEC--------------*/
/********************************/

//	pipex_child.c
void	ft_pipex_child(t_line *arg, int *fd, int fd_in, t_pipe data);
int		ft_pipex_check_in(t_line *arg, int fd_in);
int		ft_pipex_check_out(t_line *arg, int *fd);

//	pipex_main.c
int		pipex_entry(t_line *arg, t_env **env);

// pipex_tools.c
void	ft_pipex_clean(t_line **arg, t_pipe *data, int *fd, int fd_in);
int		ft_pipex_close(int *fd, int fd_in, t_pipe *data);
int		ft_pipex_free_return(t_line *arg, int ret);
int		ft_cpy_env(t_env **cpy, t_env *origin);

//	pipex_child_tools.c
void	ft_child_check_arg(t_line **arg, t_pipe *data, int *fd_pipe, int fd_in);
void	ft_pipex_check_cmd(t_line *arg, t_pipe *data, int fd_in, int *fd_pipe);
void	ft_pipex_child_exit_1(t_line **arg, t_pipe *data, int fd, int *fd_pipe);
void	ft_pipex_print(char *str, char *error);

#endif
