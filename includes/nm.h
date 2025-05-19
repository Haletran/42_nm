#pragma once

#include "../lib/libft/libft.h"

typedef struct s_global {
    int fds[10];
    int parameters_index;
    char **parameters;
}   t_global;

#define FORMAT_NOT_RECOGNIZED "nm: %s: file format not recognized"
