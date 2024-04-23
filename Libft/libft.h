/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:57:15 by esalmela          #+#    #+#             */
/*   Updated: 2024/02/12 15:24:06 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_stack
{
	int				value;
	int				index;
	int				seque;
	struct s_stack	*next;
}	t_stack;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
int		ft_isalnum(int argument);
int		ft_isalpha(int argument);
int		ft_isascii(int argument);
int		ft_isdigit(int argument);
int		ft_isprint(int argument);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
int		ft_tolower(int ch);
int		ft_toupper(int ch);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_lstadd_back(t_stack **lst, t_stack *new);
void	ft_lstadd_front(t_stack **lst, t_stack *new);
void	ft_lstclear(t_stack *lst);
void	ft_lstdelone(t_stack *lst, void (*del)(int*));
void	ft_lstiter(t_stack *lst, void (*f)(int *));
t_stack	*ft_lstlast(t_stack *lst);
t_stack	*ft_lstnew(int content, int index);
int		ft_lstsize(t_stack *lst);
char	*get_next_line(int fd);
char	*ft_strjoingnl(char *s1, char *s2);
char	*ft_save(char *save);
char	*give_line(char *save);
void	set_them_free(char *a, char *b);
int		ft_printf(int fd, const char *format, ...);
int		checkconvers(const char *format, va_list args, int *p, int fd);
int		putints(int n, int *p, int fd);
int		ft_putstr(char *res, int *p, int fd);
int		printchar(int a, int *p, int fd);
void	ft_put_hex(unsigned int num, const char format, int *p, int fd);
int		ft_hex_len(unsigned int num);
int		ft_print_hex(unsigned int num, const char format, int *p, int fd);
int		ft_putnbr(int n, int *p, int fd);
int		ft_putnbru(unsigned int n, int *p, int fd);
int		putuints(unsigned int n, int *p, int fd);
void	ft_put_ptr(uintptr_t num, int *p, int fd);
int		ft_ptr_len(uintptr_t num);
int		ft_print_void(unsigned long long ptr, int *p, int fd);
#endif
