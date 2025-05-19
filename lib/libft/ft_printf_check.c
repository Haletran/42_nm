/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:12:04 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/27 11:12:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_del(char format)
{
	return (format == '%');
}

int	check_specifier(char format, char specifier)
{
	return (format == specifier);
}

int	check_identifier(int len, char format, va_list args)
{
	if (check_specifier(format, 's'))
		len += ft_putstr_fd(va_arg(args, char *), 1);
	else if (check_specifier(format, 'd') || check_specifier(format, 'i'))
		len += ft_putnbr_fd(va_arg(args, int), 1);
	else if (check_specifier(format, 'c'))
		len += ft_putchar_fd(va_arg(args, int), 1);
	else if (check_specifier(format, '%'))
		len += ft_putchar_fd('%', 1);
	else if (check_specifier(format, 'u'))
		len += ft_putnbr_special(va_arg(args, unsigned int), 1);
	else if (check_specifier(format, 'x'))
		len += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	else if (check_specifier(format, 'X'))
		len += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (check_specifier(format, 'p'))
		len += v_pointer(va_arg(args, unsigned long long), "0123456789abcdef");
	return (len);
}
