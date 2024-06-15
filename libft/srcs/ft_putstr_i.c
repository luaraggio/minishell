/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:44:27 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 11:42:01 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_i(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_i(char *s)
{
	int	size;

	size = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
	{
		size += write(1, s, 1);
		s++;
	}
	return (size);
}
