#include "../includes/nm.h"

void free_params(t_params *head)
{
    t_params *tmp;

    while (head)
    {
        tmp = head->next;
        if (head->program_name)
          free(head->program_name);
        if (head->fd > 0)
          close(head->fd);
        free(head);
        head = tmp;
    }
}

void print_params_list(t_params *head)
{
    t_params *current = head;

    while (current)
    {
        printf("Index: %d\n", current->index);
        printf("File Descriptor: %d\n", current->fd);
        printf("Program Name: %s\n", current->program_name ? current->program_name : "(null)");
        printf("---------------\n");
        current = current->next;
    } 
    current = head;
}

int main(int argc, char **argv)
{
  (void)argc;
  t_global *global = ft_calloc(1, sizeof(t_global));
  global->params = NULL; 
  parse_files(global, argv);
  if (ft_lst_size(global->params) <= 0)
  {
      free(global->params);
      free(global);
      return (1);
  }
  //print_params_list(global->params);
  execute(global);
  free_params(global->params);
  free(global);
  return (1);
}
