NAME = minishell

SRC_DIR = src/
SRC = $(SRC_DIR)directory_builtins.c $(SRC_DIR)execute_builtin.c $(SRC_DIR)execution_utils.c $(SRC_DIR)executor.c $(SRC_DIR)export.c $(SRC_DIR)export_utils.c $(SRC_DIR)echo.c $(SRC_DIR)environmentbuilds.c $(SRC_DIR)free_doble_array.c $(SRC_DIR)here_doc.c $(SRC_DIR)iter_token.c \
$(SRC_DIR)lexer_utils.c $(SRC_DIR)lexer.c $(SRC_DIR)minishell.c $(SRC_DIR)piping_and_forking.c $(SRC_DIR)redirect.c $(SRC_DIR)safe_functions.c $(SRC_DIR)parse_cmd.c $(SRC_DIR)parse.c $(SRC_DIR)parse_utils.c $(SRC_DIR)parse_str_utils.c $(SRC_DIR)parse_redic.c\
$(SRC_DIR)parse_dolar.c $(SRC_DIR)signals.c $(SRC_DIR)minishell_utils.c $(SRC_DIR)token_redirec.c $(SRC_DIR)token_dolar.c $(SRC_DIR)token_str.c $(SRC_DIR)termios_signals.c $(SRC_DIR)iter_token_utils.c

OBJ = $(SRC:.c=.o)

LIBFT = -LLibft -lft

LINK_FLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -g -fsanitize=address,undefined 
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined

GREEN= \033[1;32m
RED=\033[0;31m
END= \033[0m

all: $(NAME)

$(NAME): $(OBJ)
		@echo "${RED}Compiling Minishell${END}"
		@$(MAKE) -C ./Libft
		@$(CC) $(OBJ) $(LIBFT) $(LINK_FLAGS) -o $(NAME)
		@echo "${GREEN}Minishell Compiled Successfully${END}"
		

%.o: %.c
		@$(CC) $(CFLAGS) -I. -ILibft -c $< -o $@

clean:
		@$(MAKE) clean -C ./Libft
		@rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_PAR)

fclean: clean
		@$(MAKE) fclean -C ./Libft
		@rm -f $(NAME)
		@echo "${GREEN}Minishell Cleaned${END}"

re: fclean all

.PHONY: all clean fclean bonus
