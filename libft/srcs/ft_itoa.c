/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:59:50 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 14:11:40 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*create_a(char *a, int n, int i, int j)
{
	int	remainder;

	a[i + 1] = 0;
	if (n < 0)
		a[0] = '-';
	while (i >= j)
	{
		remainder = n % 10;
		if (remainder < 0)
			remainder *= -1;
		a[i] = remainder + '0';
		i--;
		n /= 10;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		j;

	a = (char *)malloc(sizeof(char) * (size(n) + 1));
	if (!a)
		return (0);
	if (n < 0)
		j = 1;
	else
		j = 0;
	create_a(a, n, size(n) - 1, j);
	return (a);
}
