#include "libft.h"

int	ft_lst_size(t_params *a)
{
	int		size;
	t_params	*tmp;
	if (!a)
		return (0);
	size = 0;
	tmp = a;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
