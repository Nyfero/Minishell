# Colors
GREY = \e[90m
RED = \e[91m
GREEN = \e[92m
YELLOW = \e[93m
BLUE = \e[34m
PURPLE = \e[95m
CYAN = \e[96m
END = \e[39m

# folders
BUILTIN_PATH = builtin
EXEC_PATH = exec
PARSING_PATH = parsing
TOOLS_PATH = tools

#file
BUILTIN_SRCS = cd.c echo.c ft_env.c ft_export.c ft_export_utils.c ft_unset.c pwd.c

EXEC_SRCS = pipex_main.c pipex_child.c

PARSING_SRCS = ft_here_doc.c ft_parsing.c ft_line_func.c

TOOLS_SRCS = handle_signal.c ft_split_minishell.c ft_error.c ft_env_func.c ft_tools.c

#include
LIBFT_DIR = ../libft

LIBFT = $(LIBFT_DIR)/libft.a

INC = ../inc/minishell.h

#compilation
NAME = osef

CC = clang

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

SRCS = $(addprefix $(BUILTIN_PATH)/, $(BUILTIN_SRCS)) \
	$(addprefix $(EXEC_PATH)/, $(EXEC_SRCS)) \
	$(addprefix $(PARSING_PATH)/, $(PARSING_SRCS)) \
	$(addprefix $(TOOLS_PATH)/, $(TOOLS_SRCS)) \
	main.c

OBJS_PATH = objs/

OBJS = $(SRCS:.c=.o)

#rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INC)
	@ echo "$(BLUE)\n		*** Make $(NAME) ***\n$(END)"
	@ $(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME) $(LIBFT)
	@ echo "$(GREEN)\n		---$(NAME) created ---\n$(END)"

$(LIBFT):
	@ echo "$(BLUE)\n		*** Make Libft ***\n$(END)"
	@ make -C $(LIBFT_DIR)

$(OBJS_PATH):
	@ mkdir -p $(OBJS_PATH)

test: all
	@./$(NAME)

.c.o:
	@ ${CC} ${CFLAGS} -I $(INC) -c $< -o ${<:.c=.o}
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

clean:
	$(RM) $(OBJS)
	@ make clean -C $(LIBFT_DIR)
	@ echo "$(PURPLE)\n		*** Clean objects ***\n$(END)"

fclean: clean
	$(RM) $(NAME)
	@ make fclean -C $(LIBFT_DIR)
	@ echo "$(RED)\n		*** Remove $(NAME) ***\n$(END)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus test
