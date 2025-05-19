#pragma once

typedef struct s_global {
    int fds[10];
    struct s_params *params;
}   t_global;

typedef struct s_params {
    int index;
    int fd;
    char *program_name;
    struct s_params *next;
}   t_params;
