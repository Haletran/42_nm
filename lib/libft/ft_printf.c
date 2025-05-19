/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:11:28 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/27 11:11:32 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		len;
	int		c;
	va_list	args;

	len = 0;
	c = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[c])
	{
		if (check_del(format[c]) == 1)
		{
			c++;
			len = check_identifier(len, format[c], args);
		}
		else
			len += write(1, &format[c], 1);
		c++;
	}
	va_end(args);
	return (len);
}
