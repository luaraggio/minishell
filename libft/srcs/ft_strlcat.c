/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:22:14 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 14:13:31 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sp_strlen(const char *s, size_t size)
{
	size_t	n;

	n = 0;
	while (s[n] && n < size)
		n++;
	return (n);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_size;

	if (size == 0)
		return (ft_strlen(src));
	dst_size = sp_strlen(dst, size);
	if (size <= dst_size)
		return (size + ft_strlen(src));
	i = 0;
	while ((src[i]) && (i < (size - dst_size - 1)) && (i < ft_strlen(src)))
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (ft_strlen(src) + dst_size);
}
