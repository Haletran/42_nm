#include <elf.h>
#include <fcntl.h>      // open
#include <unistd.h>     // close, write, getpagesize
#include <sys/mman.h>   // mmap, munmap
#include <sys/stat.h>   // fstat
#include <stdlib.h>     // malloc, free, exit
#include <stdio.h>      // perror
#include <string.h>     // strerror
#include "../includes/nm.h"

// if no parameter given then it search for a a.out file in the current directory
// else error
// can take multiple parameter and output for each of them

int isDirectory(int fd)
{
  struct stat st;
  if (fstat(fd, &st) != 0)
    return (0);
  return (S_ISDIR(st.st_mode));
}

int getFileSize(int fd) {
  struct stat st;
  if (fstat(fd, &st) != 0)
    return (0);
  return (st.st_size);
}

// check the first 4 bytes for ELF header : 0x7F 'E' 'L' 'F'
int checkElfHeader(int fd, char *filename)
{
  int filesize = getFileSize(fd);
  if (filesize <= 0)
    return (1);
  // map the file into memory
  void *map = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
  Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
  if (ehdr->e_ident[EI_CLASS] != ELFCLASS32 && ehdr->e_ident[EI_CLASS] != ELFCLASS64)
  {
    printf("nm: %s: file format not recognized\n", filename);
    return (1);
  }
  if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3) {
    printf("nm: %s: not a valid ELF header\n", filename);
    munmap(map, filesize);
    return (1);
  }
  munmap(map, filesize);
  return (0);
}

int parse_files(t_global *glob, char **argv)
{
  if (!argv[1])
  {
    glob->fds[0] = open("a.out", O_RDONLY);
    if (glob->fds[0] == -1)
    {
      ft_putstr_fd("nm: 'a.out': No such file\n", 2);
      return (1);
    }
  }
  for (int i = 1; argv[i]; i++) {
    glob->fds[i] = open(argv[i], O_RDONLY);
    if (glob->fds[i] == -1) {
      ft_printf("nm: '%s': No such file\n", argv[i]);
    }
    else if (isDirectory(glob->fds[i]))
    {
      ft_printf("nm: Warning: '%s' is a directory\n", argv[i]);
      close(glob->fds[i]);
    }
    else if (checkElfHeader(glob->fds[i], argv[i]))
      close(glob->fds[i]);
    else {
        glob->parameters[glob->parameters_index] = ft_strdup(argv[i]);
        glob->parameters_index++;
    }
  }
  return (0);
}

void close_fds(int *fds, int size)
{
    for (int i = 0; i < size; i++)
        if (fds[i] >= 0)
            close(fds[i]);
}


int main(int argc, char **argv)
{

  // need to a linked list of all fds so that i can close all of them by indentifing the one that are open
  // the linked will be like that : parameter, fd | so the fds that are still open for exec will be closed
  t_global *global = malloc(sizeof(t_global) * 1000);
  global->parameters = malloc(sizeof(char **) * argc - 1);
  global->parameters_index = 0;
  parse_files(global, argv);
  if (global->parameters_index <= 0)
  {
      free(global->parameters);
      free(global);
      return (1);
  }
  print_tab(global->parameters);
  close_fds(global->fds, argc - 1);
  free(global->parameters[0]); // need to do a loop to free all saved parameters
  free(global->parameters);
  free(global);
  return (1);
}
