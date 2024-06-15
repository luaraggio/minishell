/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:52:45 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 11:41:49 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrs_i(int n)
{
	int		size;
	int		base;
	long	nbr;
	char	*lst;

	nbr = n;
	lst = "0123456789";
	base = ft_strlen(lst);
	size = 0;
	if (nbr < 0)
	{
		size += write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr > (base - 1))
	{
		size += ft_putnbrs_i(nbr / base);
		size += ft_putnbrs_i(nbr % base);
	}
	if (nbr < base)
		size += write(1, &lst[nbr], 1);
	return (size);
}

int	ft_putnbru_i(unsigned int n, char *lst)
{
	int				size;
	unsigned int	base;

	base = (unsigned int)ft_strlen(lst);
	size = 0;
	if (n > (base - 1))
	{
		size += ft_putnbru_i(n / base, lst);
		size += ft_putnbru_i(n % base, lst);
	}
	if (n < base)
		size += write(1, &lst[n], 1);
	return (size);
}

int	ft_putptr_i(unsigned long n, int index)
{
	int				size;
	unsigned long	base;
	char			*lst;

	base = 16;
	lst = "0123456789abcdef";
	size = 0;
	if (n == 0 && index == 0)
		return (write(1, "(nil)", 5));
	if (index == 0)
		size += ft_putstr_i("0x");
	if (n > (base - 1))
	{
		size += ft_putptr_i(n / base, index + 1);
		size += ft_putptr_i(n % base, index + 1);
	}
	if (n < base)
		size += write(1, &lst[n], 1);
	return (size);
}
