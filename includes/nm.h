#pragma once
#include <elf.h>
#include <fcntl.h>      // open
#include <unistd.h>     // close, write, getpagesize
#include <sys/mman.h>   // mmap, munmap
#include <sys/stat.h>   // fstat
#include <stdlib.h>     // malloc, free, exit
#include <stdio.h>      // perror
#include <string.h>     // strerror
#include "../lib/libft/libft.h"
#include "lst.h"

int isDirectory(int fd);
int getFileSize(int fd);
int checkElfHeader(int fd, char *filename);
int parse_files(t_global *glob, char **argv);
int execute(t_global *global);
