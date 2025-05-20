#include "libft.h"

void	*ft_lst_new(int fd, char *program_name, int index)
{
	t_params	*elem;

	elem = malloc(sizeof(t_params));
	if (!elem)
		return (NULL);
	elem->fd = fd;
	elem->program_name = program_name;
	elem->index = index;
	elem->next = NULL;
	return (elem);
}
