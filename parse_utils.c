#include "minishell.h"

void    current_itoken(t_data *data)
{
    int i;

    i = data->i_token;
    while (data->lexer_array[i].type != TOKEN_EOL
            && data->lexer_array[i].type != TOKEN_PIPE)
        i++;
    data->i_token = i + 1;
}

int index_after_quate(t_data *data, int i)
{
    while (data->lexer_array[i].type != TOKEN_EOL
            && data->lexer_array[i].type != TOKEN_PIPE
            && is_redic(data, i) == false
            && data->lexer_array[i].type != TOKEN_SPACE)
        i++;
    return (i);
}

int	ft_cont_str(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			i++;
			j++;
		}
		if (*s == c && j != 0)
			j = 0;
		s++;
	}
	return (i);
}
char    **copy_realloc(char *str, char **new_ptr, int i, int size)
{
    int end;

    end = 0;
    while (++i < size - 1)
    {
        while (*str == ' ' && *str)
            str++;
		end = 0;
		while (str[end] != ' ' && str[end])
			end++;
		new_ptr[i] = ft_substr(str, 0, end);
        if (!new_ptr[i])
        {
            free_args(new_ptr);
            return (NULL);
        }
        str = str + end;
    }
    return (new_ptr);
}

char    **ft_realloc_char_array(char *str, t_parse *parse, t_data *data,
                                size_t new_size) 
{
    char **new_ptr;
    int i;

    new_ptr = calloc(new_size + 1, sizeof(char *));
    if (new_ptr == NULL) 
        return NULL;
    if (data->i_str > 0)
    {
        i = -1;
        while (++i < data->i_str)
            new_ptr[i] = ft_strdup(parse[data->i_parse].cmd[i]);
    }
    i = 0;
    while (new_ptr[i])
    {
        printf("%d\n", data->i_str);
        printf("reac: %s\n", parse[data->i_parse].cmd[i]);
        i++;
    }
    //free_args(parse[data->i_parse].cmd);
    str = ft_strchr(str, '=') + 1;
    i = data->i_str - 1;
    new_ptr = copy_realloc(str, new_ptr, i, new_size);
    return (new_ptr);
}
