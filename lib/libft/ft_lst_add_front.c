#include "libft.h"

void	ft_lst_add_front(t_params **a, t_params *new)
{
	if (a)
	{
		if (*a)
			new->next = *a;
		*a = new;
	}
}
