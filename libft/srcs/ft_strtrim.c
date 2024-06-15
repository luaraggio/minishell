/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:21:53 by dherszen          #+#    #+#             */
/*   Updated: 2023/11/07 17:35:07 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Rever para refatorar usando strchr...
*/
#include "libft.h"

static int	char_in_set(const char *set, const char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_start_i(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && char_in_set(set, s1[i]))
		i++;
	return (i);
}

static char	*malloc_function(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (0);
	if (size == 1)
		str[0] = 0;
	return (str);
}

static size_t	ft_end_i(const char *s1, const char *set)
{
	int	i;

	i = (int)(ft_strlen(s1) - 1);
	while (char_in_set(set, s1[i]))
		i--;
	i++;
	return ((size_t)i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	size_t	start_i;
	size_t	end_i;
	size_t	i;

	if (!s1)
		return (0);
	start_i = ft_start_i(s1, set);
	end_i = ft_end_i(s1, set);
	if (start_i == ft_strlen(s1))
		return (malloc_function(1));
	str = (char *)malloc(sizeof(char) * ((end_i - start_i) + 1));
	if (!str)
		return (0);
	i = -1;
	while (++i < (end_i - start_i) && s1[start_i + i])
		str[i] = s1[start_i + i];
	str[i] = 0;
	return (str);
}
