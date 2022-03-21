# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgourlin <jgourlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 14:07:19 by gsap              #+#    #+#              #
#    Updated: 2022/03/21 15:05:17 by jgourlin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# valgrind --leak-check=full --track-fds=yes --trace-children=yes --track-origins=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

#	Colors
GREY = \e[90m
RED = \e[91m
GREEN = \e[92m
YELLOW = \e[93m
BLUE = \e[34m
PURPLE = \e[95m
CYAN = \e[96m
END = \e[39m

#	Showing command
DISP = FALSE

ifeq ($(DISP),TRUE)
	HIDE =
else
	HIDE = @
endif

#	Includes
INC = inc/

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

#	Folders
SRCS_PATH = srcs

#	Files
FILES = main.c ft_env_func.c ft_parsing.c ft_split_minishell.c fill_line.c garbage_free.c \
	ft_line_func.c ft_limiteur.c ft_here_doc.c ft_expand.c ft_infile.c ft_outdir.c \
	ft_del_redir.c ft_check_inpt.c ft_expand_utils.c ft_outdir_utils.c\
	echo.c pwd.c env.c unset.c export.c cd.c cd_tools.c ft_export_utils.c exit.c\
	pipex_main.c pipex_child.c pipex_tools.c pipex_child_tools.c\
	ft_error.c ft_tools.c ft_quotes.c\
	sig_init.c sig_handling.c

#	Compilation
NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = $(addprefix $(SRCS_PATH)/, $(FILES))

OBJS_PATH = objs/

OBJS = $(patsubst $(SRCS_PATH)%.c,	$(OBJS_PATH)%.o, $(SRCS))

#	Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_PATH) $(OBJS) $(INC)/minishell.h
	@ echo "$(BLUE)\n		*** Make $(NAME) ***\n$(END)"
	$(HIDE) $(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME) $(LIBFT)
	@ echo "$(GREEN)\n		---$(NAME) created ---\n$(END)"

$(LIBFT): libft/Makefile
	@ echo "$(BLUE)\n		*** Make Libft ***\n$(END)"
	$(HIDE) make -C $(LIBFT_DIR)

$(OBJS_PATH):
	$(HIDE) mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)/$(NAME).h Makefile
	$(HIDE) $(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

clean:
	$(HIDE) $(RM) $(OBJS_PATH)
	$(HIDE) make clean -C $(LIBFT_DIR)
	@ echo "$(PURPLE)\n		*** Clean objects ***\n$(END)"

fclean: clean
	$(HIDE) $(RM) $(NAME)
	$(HIDE) make fclean -C $(LIBFT_DIR)
	@ echo "$(RED)\n		*** Remove $(NAME) ***\n$(END)"

re: fclean all

.PHONY: all clean fclean re
