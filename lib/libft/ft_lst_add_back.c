#include "libft.h"

void	ft_lstadd_back(t_params **lst, int fd, char *program_name)
{
    t_params	*new;
    t_params	*tmp;
    int			index;

    if (!lst)
        return;
    index = ft_lst_size(*lst) + 1;
    new = ft_lst_new(fd, program_name, index);
    if (!*lst)
    {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
