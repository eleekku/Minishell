# include "minishelld.h"

t_char_iter	char_iter_constructor(char *start, size_t len)
{
	t_char_iter	iter;

	iter.start = start;
	iter.end = start + len;
	return (iter);
}

char	*char_iter_cursor(t_char_iter *self)
{
	return (self->start);
}

char	char_iter_peek(t_char_iter *self)
{
	return (*self->start);
}

char	char_iter_peek_next(t_char_iter *self)
{
	return (*(self->start + 1));
}

char	char_iter_next(t_char_iter *self)
{
	char	next;

	next = *self->start + 1;
	self->start++;
	return (next);
}
char	*char_find_dq(t_char_iter *self)
{
	size_t	len;

	len = 1;
	while (*(self->end - len) != '"')
	{
		len++;
	}
	return (self->end - len);
}
int	ft_realloc(t_token **token, size_t size)
{
	t_token		*new;
	size_t		i;

	new = ft_calloc(size, sizeof(t_token));
	if (!new)
		return (1);
	i = 0;
	while (i < size - 1)
	{
		new[i] = (*token)[i];
		i++;
	}
	free(*token);
	*token = new;
	return (0);
}

