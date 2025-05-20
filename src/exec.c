#include "../includes/nm.h"

static int checkIfSymbols(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr) {
  uint16_t shnum = ehdr->e_shnum;
  if (shnum == 0)
    shnum = shdr[0].sh_size;
  for (int i = 0; i < shnum; i++) {
    if ((shdr[i].sh_type == SHT_SYMTAB) && shdr[i].sh_size > 0) {
      return (1);
    }
  }
  return (0);
}

// need to make this function better since GPT made it, too long and too much
// symbol handle
char get_symbol_type(Elf64_Sym sym, Elf64_Shdr *shdr, uint16_t shnum) {
  unsigned char bind = ELF64_ST_BIND(sym.st_info);
  unsigned char type = ELF64_ST_TYPE(sym.st_info);

  char c = '?';

  if (bind == STB_WEAK) {
    if (type == STT_OBJECT) {
      c = (sym.st_shndx == SHN_UNDEF) ? 'v' : 'V';
    } else {
      c = (sym.st_shndx == SHN_UNDEF) ? 'w' : 'W';
    }
  } else if (sym.st_shndx == SHN_UNDEF) {
    c = 'U';
  } else if (sym.st_shndx == SHN_COMMON) {
    c = 'C';
  } else if (sym.st_shndx >= shnum) {
    c = '?';
  } else {
    Elf64_Shdr sec = shdr[sym.st_shndx];
    if (sec.sh_type == SHT_NOBITS) {
      c = 'B';
    } else if (sec.sh_flags & SHF_EXECINSTR) {
      c = 'T';
    } else if (sec.sh_flags & SHF_WRITE) {
      c = 'D';
    } else {
      c = 'R';
    }
  }
  if (bind == STB_LOCAL && c != '?' && c != 'U')
    c = ft_tolower(c);
  return c;
}

// thks GPT, need to understand it fully, easy to understand but need to be able
// to replicated it
void sort_symtabs(t_symtabs *tabs) {
  for (int i = 0; i < tabs->size - 1; i++) {
    for (int j = 0; j < tabs->size - i - 1; j++) {
      if (strcmp(tabs->name[j], tabs->name[j + 1]) > 0) {
        const char *tmp_name = tabs->name[j];
        tabs->name[j] = tabs->name[j + 1];
        tabs->name[j + 1] = tmp_name;

        uint64_t tmp_value = tabs->value[j];
        tabs->value[j] = tabs->value[j + 1];
        tabs->value[j + 1] = tmp_value;

        char tmp_type = tabs->type[j];
        tabs->type[j] = tabs->type[j + 1];
        tabs->type[j + 1] = tmp_type;
      }
    }
  }
}

void print_symtab(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, void *file_mem) {
  struct s_symtabs *res = ft_calloc(1, sizeof(t_symtabs));
  uint16_t shnum = ehdr->e_shnum;
  if (shnum == 0)
    shnum = shdr[0].sh_size;

  for (int i = 0; i < shnum; i++) {
    if (shdr[i].sh_type == SHT_SYMTAB) {
      Elf64_Sym *symtab = (Elf64_Sym *)((char *)file_mem + shdr[i].sh_offset);
      size_t num_syms = shdr[i].sh_size / sizeof(Elf64_Sym);
      const char *strtab =
          (const char *)file_mem + shdr[shdr[i].sh_link].sh_offset;

      res->name = ft_calloc(num_syms, sizeof(char *));
      res->type = ft_calloc(num_syms, sizeof(char));
      res->value = ft_calloc(num_syms, sizeof(uint64_t));
      res->size = 0;

      for (size_t j = 0; j < num_syms; j++) {
        const char *name = strtab + symtab[j].st_name;
        if (name[0] == '\0')
          continue;
        res->name[res->size] = (char *)name;
        res->value[res->size] = symtab[j].st_value;
        res->type[res->size] = get_symbol_type(symtab[j], shdr, shnum);
        res->size += 1;
      }
      sort_symtabs(res);
      for (int i = 0; i < res->size; i++) {
        if (res->type[i] != '?') {
          if (res->type[i] == 'U' || res->type[i] == 'w')
            printf("                 %c %s\n", res->type[i], res->name[i]);
          else
            printf("%016lx %c %s\n", res->value[i], res->type[i], res->name[i]);
        }
      }
      free(res->value);
      free(res->type);
      free(res->name);
      free(res);
    }
  }
}

int execute(t_global *global) {
  struct s_params *tmp = global->params;
  int filesize = 0;
  Elf64_Ehdr *ehdr;
  Elf64_Shdr *shdr;

  while (tmp) {
    if (ft_lst_size(global->params) > 1)
      ft_printf("\n%s:\n", tmp->program_name);
    filesize = getFileSize(tmp->fd);
    void *file_mem = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, tmp->fd, 0);
    // add error check here

    ehdr = (Elf64_Ehdr *)file_mem;
    shdr = (Elf64_Shdr *)((char *)file_mem + ehdr->e_shoff);
    if (checkIfSymbols(ehdr, shdr) == 0) {
      ft_printf("nm: %s: no symbols\n", tmp->program_name);
    } else {
      print_symtab(ehdr, shdr, file_mem);
    }
    munmap(file_mem, filesize);
    close(tmp->fd);
    tmp = tmp->next;
  }
  return (0);
}
