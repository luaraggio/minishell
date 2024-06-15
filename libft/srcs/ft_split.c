/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:31:39 by dherszen          #+#    #+#             */
/*   Updated: 2023/11/01 13:02:05 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	word_clear(char **dst, int size)
{
	while (size >= 0)
	{
		free(dst[size]);
		size--;
	}
}

static size_t	c_word(const char *s, char c)
{
	size_t	n;
	size_t	i;

	if (s[0] == 0)
		return (0);
	if (s[0] == c)
		s++;
	n = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || (i >= 1 && s[i - 1] == c)))
			n++;
		i++;
	}
	return (n);
}

static void	c_split(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			*s = 0;
		s++;
	}
}

static int	split_loop(char **dest, char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (src[i] != 0)
		{
			dest[j] = (char *)malloc(sizeof(char) * (ft_strlen(&src[i]) + 1));
			if (!dest[j])
			{
				if (j > 0)
					word_clear(dest, j - 1);
				return (0);
			}
			i += ft_strlcpy(dest[j], &src[i], (ft_strlen(&src[i]) + 1));
			j++;
		}
		if (src[i] == 0)
			i++;
	}
	dest[j] = 0;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	*s_copy;
	char	**dest;

	if (!s)
		return (0);
	s_copy = ft_strdup(s);
	if (s_copy == 0)
		return (0);
	dest = (char **)malloc(sizeof(char *)
			* ((c_word(s, c)) + 1));
	if (!dest)
		return (0);
	c_split(s_copy, c);
	if (split_loop(dest, s_copy, ft_strlen(s)) == 0)
	{
		free(s_copy);
		free(dest);
		return (0);
	}
	free(s_copy);
	return (dest);
}
