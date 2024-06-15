/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:50:12 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/26 13:35:30 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sf_strcpy(char *dest, const char *src, size_t dest_i)
{
	size_t	i;

	i = 0;
	while (i < (ft_strlen(src)))
	{
		dest[i + dest_i] = src[i];
		i++;
	}
	dest[i + dest_i] = 0;
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (0);
	str = sf_strcpy(str, s1, 0);
	str = sf_strcpy(str, s2, ft_strlen(s1));
	return (str);
}
