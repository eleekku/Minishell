#include "minishell.h"

bool   change_str_dolar(t_data *data, t_parse *parse, char *str, int i_token)
{
    int re_size;
    int len;
    
    len = data->lexer_array[i_token].pos.len;
    if (ft_strchr(str, ' ') == NULL)
    {
        parse[data->i_parse].cmd[data->i_str] = ft_strdup(str + len);
        return (true);
    }
    //check for null
    else
    {   
        re_size = ft_cont_str(ft_strchr(str, '=') + 1, ' ') + data->i_str;
        str = ft_strchr(str, '=') + 1;
        while (data->i_str < re_size)
        {
            while (*str == ' ' && *str)
                str++;
		    int end = 0;
		    while (str[end] != ' ' && str[end])
			    end++;
            parse[data->i_parse].cmd[data->i_str] = ft_substr(str, 0, end);
            str = str + end;
            data->i_str++;
        }
        return (true);
    }
    //check for null
    return (false);
} 

char    *str_redc_dolar(t_data *data, int i_token)
{
    char *str;
    int len;

    len = data->lexer_array[i_token].pos.len;
    if (data->lexer_array[i_token].pos.start[0] == '$' && len == 1)
        return (ft_strdup("$"));
    if (data->lexer_array[i_token].pos.start[0] == '?')
    {
        str = ft_itoa(data->exit_status);
        //check for NULL
        return (str);
    }
    else
        str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len);
    //check for null;
    str = check_str_envp_redc(data, str, i_token);
    return (str);
    //check for NULL
}

char *parse_dolar_dquate(t_data *data, int i_token)
{
    char *str;
    char **envp;
    int i;
    int len;

    envp = data->env;
    len = data->lexer_array[i_token].pos.len;
    str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len);
    i = 0;
    while (envp[i])
    {
        if (*str == '$' && ft_strlen(str) == 1)
            return(str);
        len = ft_strchr(envp[i], '=') - envp[i];
        if (ft_strncmp(envp[i], str + 1, len) == 0 && len + 1 == (int)ft_strlen(str))
        {
            free(str);
            str = ft_strdup(envp[i] + data->lexer_array[i_token].pos.len);
            return (str);
        }
        i++;
    }
    free(str);
    str = ft_strdup("");
    return (str);
}

bool parse_dolar_envp(t_data *data, t_parse *parse, char *str, int i_token)//str + 1 is because str = $something
{
    int i;
    char **envp;
    size_t len;

    i = 0;
    envp = data->env;
    while (envp[i])
    {
        if (*str == '$' && ft_strlen(str) == 1)
        {   
            parse->cmd[data->i_str] = str;
            return (true);
        }
        len = ft_strchr(envp[i], '=') - envp[i];
        if (ft_strncmp(envp[i], str + 1, len) == 0 && len + 1 == ft_strlen(str))
        {
            free(str);
            if (change_str_dolar(data, parse, envp[i], i_token) == true)
                return (true);   
        }
        i++;
    }
    return (false);
}
