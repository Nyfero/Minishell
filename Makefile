# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 14:07:19 by gsap              #+#    #+#              #
#    Updated: 2022/02/28 11:56:39 by gsap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# valgrind --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

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
FILES = main.c echo.c pwd.c handle_signal.c ft_split_minishell.c ft_line_func.c \
	ft_parsing.c ft_error.c ft_env_func.c ft_env.c ft_unset.c ft_export.c \
	cd.c ft_export_utils.c ft_tools.c ft_here_doc.c \
	pipex_main.c pipex_child.c

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