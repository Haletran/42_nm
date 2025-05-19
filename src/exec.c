#include "../includes/nm.h"


int execute(t_global *global)
{
  struct s_params *tmp = global->params;
  int filesize = 0;
      Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    Elf64_Sym *symtab;
    const char *strtab;
    int num_syms, i;

  while (tmp)
  {
    filesize = getFileSize(tmp->fd);
    void *file_mem = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, tmp->fd, 0);
    ehdr = (Elf64_Ehdr *)file_mem;
    shdr = (Elf64_Shdr *)((char *)file_mem + ehdr->e_shoff);

    // Find the symbol table and corresponding string table
    for (int j = 0; j < ehdr->e_shnum; j++) {
      if (shdr[j].sh_type == STB_WEAK) {
        symtab = (Elf64_Sym *)((char *)file_mem + shdr[j].sh_offset);
        num_syms = shdr[j].sh_size / shdr[j].sh_entsize;
        // Get the string table for symbol names
        strtab = (const char *)file_mem + shdr[shdr[j].sh_link].sh_offset;

        // need to parse to only get the important symbols that nm prints by default
        //  instead of all of them r, U, T, t, d, w, D, B
        for (i = 0; i < num_syms; i++) {
            printf("0x%016lx %c %s\n",
                symtab[i].st_value,
                ELF64_ST_BIND(symtab[i].st_info) == STB_GLOBAL ? 'G' : 'W',
                strtab + symtab[i].st_name);
        }
      }
    }
    file_mem = NULL;
    ehdr = NULL;
    shdr = NULL;
    symtab = NULL;
    munmap(file_mem, filesize);
    close(tmp->fd);
    tmp = tmp->next;
  }
  return (0);
}

