/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:53:50 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 11:53:33 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	ft_parse_str(va_list *args, char c)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_putchar_i(va_arg(*args, int));
	else if (c == 'i' || c == 'd')
		size += ft_putnbrs_i(va_arg(*args, int));
	else if (c == 's')
		size += ft_putstr_i(va_arg(*args, char *));
	else if (c == 'u')
		size += ft_putnbru_i(va_arg(*args, unsigned int), "0123456789");
	else if (c == 'x')
		size += ft_putnbru_i(va_arg(*args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		size += ft_putnbru_i(va_arg(*args, unsigned int), "0123456789ABCDEF");
	else if (c == '%' || c == 0)
		size += ft_putchar_i('%');
	else if (c == 'p')
		size += ft_putptr_i((unsigned long)va_arg(*args, void *), 0);
	else
		size += ft_printf("%%%c", c);
	return (size);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		size;
	va_list	args;

	va_start(args, format);
	size = 0;
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1])
				i++;
			size += ft_parse_str(&args, format[i]);
		}
		else
			size += ft_putchar_i(format[i]);
	}
	va_end(args);
	return (size);
}
