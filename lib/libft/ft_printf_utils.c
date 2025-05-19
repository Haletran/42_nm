/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:12:31 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/27 11:12:34 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_special(unsigned int n, unsigned int fd)
{
	int	len;

	len = 0;
	if (n > 9)
	{
		len += ft_putnbr_fd(n / 10, fd);
		len += ft_putnbr_fd(n % 10, fd);
	}
	else
		len += ft_putchar_fd('0' + n, fd);
	return (len);
}

int	ft_putnbr_base(unsigned int nb, char *base)
{
	int	i;
	int	quotient;

	i = 0;
	quotient = nb / 16;
	if (quotient > 0)
		i = ft_putnbr_base(quotient, base);
	return (i + ft_putchar_fd(base[nb % 16], 1));
}

int	ft_putnbr_base_ptr(unsigned long long nb, char *base)
{
	int					i;
	unsigned long long	quotient;

	i = 0;
	quotient = nb / 16;
	if (quotient > 0)
		i = ft_putnbr_base_ptr(quotient, base);
	return (i + ft_putchar_fd(base[nb % 16], 1));
}

int	v_pointer(unsigned long long ptr, char *base)
{
	int	len;

	len = 0;
	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	len += ft_putstr_fd("0x", 1);
	len += ft_putnbr_base_ptr(ptr, base);
	return (len);
}
