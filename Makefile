NAME = minishell

SRC = execute_builtin.c execution_utils.c executor.c export.c export_utils.c echo.c environmentbuilds.c free_doble_array.c ft_skip_split.c iter_token.c \
lexer_utils.c lexer.c minishell.c piping_and_forking.c pwd.c redirect.c safe_functions.c parse_cmd.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

OBJ_PAR = $(PAR:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -lreadline
# -g -fsanitize=address,undefined

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_PAR)
		$(MAKE) -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ) $(OBJ_PAR) $(LIBFT) -o $(NAME)

#bonus: .bonus

#.bonus: $(OBJ_BONUS) $(OBJ_PAR)
#		$(MAKE) -C ./libft
#	#	$(CC) $(FLAGS) -I. -Ilibft $(OBJ_BONUS) $(OBJ_PAR) $(LIBFT) -o $(NAME)
#	#	@touch .bonus

%.o: %.c
		$(CC) $(FLAGS) -I. -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_PAR)
		@rm -f .bonus

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus
