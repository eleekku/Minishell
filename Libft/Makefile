# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 15:14:06 by esalmela          #+#    #+#              #
#    Updated: 2024/02/07 15:25:14 by esalmela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FT_PRINTF = ft_printf/libftprintf.a
NAME = libft.a

CC = @cc
CFLAGS = -Wall -Wextra -Werror
AR = @ar rcs
RM = @rm -f

FILES = ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strlcpy \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_strdup \
		ft_strjoin \
		ft_substr \
		ft_putstr_fd \
		ft_split \
		ft_strtrim \
		ft_itoa \
		ft_striteri \
		ft_putchar_fd \
		ft_strmapi \
		ft_putendl_fd \
		ft_putnbr_fd \
		get_next_line \
		get_next_line_utils \
		ft_printf \
		ft_print_void \
		ft_printf_hex \
		ft_printf_utils \

FILES_B =   ft_lstnew_bonus \
	  		ft_lstadd_front_bonus \
	  		ft_lstsize_bonus \
	  		ft_lstlast_bonus \
	  		ft_lstadd_back_bonus \
	  		ft_lstdelone_bonus \
	  		ft_lstclear_bonus \
	  		ft_lstiter_bonus \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

bonus: .bonus

.bonus: $(OBJS_B)
	$(AR) $(NAME) $^
	@touch .bonus

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
