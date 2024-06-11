NAME = minishell

SRC = directory_builtins.c execute_builtin.c execution_utils.c executor.c export.c export_utils.c echo.c environmentbuilds.c free_doble_array.c here_doc.c iter_token.c \
lexer_utils.c lexer.c minishell.c piping_and_forking.c redirect.c safe_functions.c parse_cmd.c parse.c parse_utils.c parse_str_utils.c parse_redic.c\
parse_dolar.c signals.c minishell_utils.c token_redirec.c token_dolar.c token_str.c termios_signals.c iter_token_utils.c

OBJ = $(SRC:.c=.o)

LIBFT = -LLibft -lft

LINK_FLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -g -fsanitize=address,undefined 
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined
# -g -fsanitize=address,undefined

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./Libft
		$(CC) $(OBJ) $(LIBFT) $(LINK_FLAGS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -I. -ILibft -c $< -o $@

clean:
		$(MAKE) clean -C ./Libft
		rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_PAR)
		@rm -f .bonus

fclean: clean
		$(MAKE) fclean -C ./Libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus
