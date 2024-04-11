# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 20:08:53 by esalmela          #+#    #+#              #
#    Updated: 2023/11/20 20:08:57 by esalmela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = @cc
CFLAGS = -Wall -Wextra -Werror
AR = @ar rcs
RM = @rm -f

FILES = ft_printf \
		ft_print_void \
		ft_printf_hex \
		ft_printf_utils \

SRCS_DIR = ./
SRCS = $(SRCS_DIR)$(FILES:%=%.c)

OBJS_DIR = ./
OBJS = $(OBJS_DIR)$(FILES:%=%.o)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
