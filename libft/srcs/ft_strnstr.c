/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:35:21 by dherszen          #+#    #+#             */
/*   Updated: 2023/10/30 11:40:03 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && len == 0)
		return (0);
	if (!*little)
		return ((char *)(big));
	i = 0;
	while (i < ft_strlen(big) && i < len)
	{
		j = 0;
		while (little[j] && j < len - i && (little[j] == big[i + j]))
		{
			if (little[j + 1] == 0)
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	return (0);
}
