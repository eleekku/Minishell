NAME = minishell

SRC = execute_builtin.c execution_utils.c executor.c export.c export_utils.c echo.c environmentbuilds.c free_doble_array.c ft_skip_split.c iter_token.c \
lexer_utils.c lexer.c minishell.c piping_and_forking.c pwd.c redirect.c safe_functions.c parse_cmd.c parse.c parse_utils.c parse_str_utils.c parse_redic.c\
parse_dolar.c signals.c

OBJ = $(SRC:.c=.o)


LIBFT = -Llibft -lft

LINK_FLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -g -fsanitize=address,undefined 
CC = cc
CFLAGS = -g -fsanitize=address,undefined -Wall -Wextra -Werror -I. -Ilibft -I /Users/$(USER)/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) $(OBJ) $(LIBFT) $(LINK_FLAGS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_PAR)
		@rm -f .bonus

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus
