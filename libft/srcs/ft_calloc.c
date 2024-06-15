/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:23:45 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/28 18:08:04 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dst;

	if (nmemb != 0 && size != 0 && ((nmemb * size) / nmemb) != size)
		return (0);
	dst = (char *)malloc(nmemb * size);
	if (!dst)
		return (0);
	ft_bzero(dst, (nmemb * size));
	return (dst);
}
