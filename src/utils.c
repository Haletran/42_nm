#include "../includes/nm.h"

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


int ft_strsize(char **str)
{
  int size = 0;
  for (int i = 0; str[i]; i++)
    size++;
  return (size);
}

int parse_files(t_global *glob, char **argv)
{
  int argc = ft_strsize(argv);
  int *fds = ft_calloc(argc, sizeof(int));
  if (!fds)
    return (1);

  int nb_files = 0;
  if (!argv[1])
  {
    fds[0] = open("a.out", O_RDONLY);
    if (fds[0] == -1)
    {
      ft_putstr_fd("nm: 'a.out': No such file\n", 2);
      free(fds);
      return (1);
    }
    nb_files = 1;
    ft_lstadd_back(&(glob->params), fds[0], ft_strdup("a.out"));
  }
  else
  {
    for (int i = 1; argv[i]; i++) {
      fds[nb_files] = open(argv[i], O_RDONLY);
      if (fds[nb_files] == -1) {
        ft_printf("nm: '%s': No such file\n", argv[i]);
      }
      else if (isDirectory(fds[nb_files]))
      {
        ft_printf("nm: Warning: '%s' is a directory\n", argv[i]);
        close(fds[nb_files]);
      }
      else if (checkElfHeader(fds[nb_files], argv[i]))
        close(fds[nb_files]);
      else {
        ft_lstadd_back(&(glob->params), fds[nb_files], ft_strdup(argv[i]));
      }
      nb_files++;
    }
  }
  free(fds);
  return (0);
}
