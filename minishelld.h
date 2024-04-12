#ifndef MINISHELLD_H
# define MINISHELLD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
    char **env;
    char **str_rl;
} t_data;

# endif