#include <elf.h>
#include <fcntl.h>      // open
#include <unistd.h>     // close, write, getpagesize
#include <sys/mman.h>   // mmap, munmap
#include <sys/stat.h>   // fstat
#include <stdlib.h>     // malloc, free, exit
#include <stdio.h>      // perror
#include <string.h>     // strerror
#include "nm.h"

// if no parameter given then it search for a a.out file in the current directory
// else error
// can take multiple parameter and output for each of them

int ft_strlen(char *str)
{
  int len = 0;

  for (int i = 0; str[i]; i++) {
    len++; 
  }
  return (len);
}


void ft_putstr(int fd, char *str)
{
     write(fd, str, ft_strlen(str)); 
}

int parse_files(t_global *glob, char **argv)
{
  int nb_errors = 0;
  // open all files and check if ELF header
  if (!argv[1])
  {
    glob->fds[0] = open("a.out", O_RDONLY);
    if (glob->fds[0] == -1)
    {
      ft_putstr(2, "ft_nm: 'a.out': No such file");
      return (1);
    }
  }
  for (int i = 0; argv[i]; i++) {
    glob->fds[i] = open(argv[i], O_RDONLY);
    if (glob->fds[i] == -1) {
      ft_putstr(2, "ft_nm: '");
      ft_putstr(2, argv[i]);
      ft_putstr(2, "': No such file\n");
      nb_errors++;
    }
  }
  return (nb_errors);
}

int main(int argc, char **argv)
{
  (void)argc;
  t_global *global = malloc(sizeof(t_global) * 1000);
  if (parse_files(global, argv))
      return (1);
  ft_putstr(1, "Execution haha"); 
  //execute(argv);
  free(global);
  return (1);
}
