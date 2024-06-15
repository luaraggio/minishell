/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:37:18 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 11:04:17 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(size_t len, const char *sub)
{
	size_t	i;

	i = 0;
	while ((i < len) && (sub[i]))
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	if (((size_t)start >= ft_strlen(s)) || (len == 0))
	{
		str = (char *)malloc(sizeof(char) * 1);
		if (!str)
			return (0);
		str[0] = 0;
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (count(len, &s[start]) + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < (count(len, &s[start])))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
