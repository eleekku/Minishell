NAME = minishell

SRC = build_export.c echo.c environmentbuilds.c free_doble_array.c ft_skip_split.c iter_token.c \
lexer_utils.c lexer.c minishell.c pwd.c safe_functions.c check_command.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

OBJ_PAR = $(PAR:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -g -fsanitize=address,undefined -lreadline 

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_PAR)
		$(MAKE) -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ) $(OBJ_PAR) $(LIBFT) -o $(NAME)

bonus: .bonus

.bonus: $(OBJ_BONUS) $(OBJ_PAR)
		$(MAKE) -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ_BONUS) $(OBJ_PAR) $(LIBFT) -o $(NAME)
		@touch .bonus

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
