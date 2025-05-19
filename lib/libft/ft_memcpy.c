/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:29:44 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/09 15:01:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t			s;
	unsigned char	*temp;
	unsigned char	*temp2;

	s = 0;
	if (src == 0 && dest == 0)
		return (0);
	temp = (unsigned char *)dest;
	temp2 = (unsigned char *)src;
	while (size)
	{
		temp[s] = temp2[s];
		s++;
		size--;
	}
	return (temp);
}
