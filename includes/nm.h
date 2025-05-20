#pragma once
#include "../lib/libft/libft.h"
#include "lst.h"
#include <elf.h>
#include <fcntl.h>    // open
#include <stdio.h>    // perror
#include <stdlib.h>   // malloc, free, exit
#include <string.h>   // strerror
#include <sys/mman.h> // mmap, munmap
#include <sys/stat.h> // fstat
#include <unistd.h>   // close, write, getpagesize

int isDirectory(int fd);
int getFileSize(int fd);
int checkElfHeader(int fd, char *filename);
int parse_files(t_global *glob, char **argv);
int execute(t_global *global);
int ft_strsize(char **str);
