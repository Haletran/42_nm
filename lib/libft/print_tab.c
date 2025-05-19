#include "libft.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i]) {
			ft_putstr_fd(tab[i], 1);
		}
		i++;
	}
}
