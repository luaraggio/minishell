/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:17:00 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/28 17:16:14 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	pos;

	pos = ft_strlen(s);
	if ((unsigned char)c == 0)
		return ((char *)(s + pos));
	while (pos >= 0)
	{
		if (s[pos] == (unsigned char)c)
			return ((char *)(s + pos));
		pos--;
	}
	return (0);
}
