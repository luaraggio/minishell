/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:32:06 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/24 10:48:59 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest <= src)
		return ((void *)(ft_memcpy(dest, src, n)));
	else
	{
		while (n >= 1)
		{
			n--;
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
		return ((void *)dest);
	}
}
