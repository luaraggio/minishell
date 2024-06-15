/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:25:39 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 16:45:35 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* calculates the length of a string. */
ssize_t	ft_strlen_gnl(const char *s)
{
	ssize_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

/** Checks if a newline character is present in the last node of the storage
* list. It returns 1 if a newline character is not present or if the storage
* list is empty, and 0 if a newline character is present. */
int	new_line_not_present(t_glist *storage)
{
	int		i;
	t_glist	*current;

	if (storage == 0)
		return (1);
	current = ft_lst_last(storage);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

/** Returns the last node in the storage list. If the storage list is empty,
* it returns 0. It does this by traversing the list until it reaches a node
* that does not have a next node. */
t_glist	*ft_lst_last(t_glist *storage)
{
	if (storage == 0)
		return (0);
	while (storage->next)
		storage = storage->next;
	return (storage);
}

/** Allocates mem for the line to be extracted from the storage list.
* It calculates the size of the line by counting the number of characters
* in the storage list until it encounters a '\n' or reaches the end of the
* list. Then allocates the mem for a string of that size plus one
* (for '\0').*/
void	malloc_line(char **line, t_glist *storage)
{
	int	size;
	int	i;

	size = 0;
	while (storage)
	{
		i = 0;
		while (storage->content[i] && storage->content[i] != '\n')
		{
			size++;
			i++;
		}
		if (storage->content[i] == '\n')
			size++;
		storage = storage->next;
	}
	*line = (char *)malloc(sizeof(char) * (size + 1));
}

/** Frees the memory used by the storage list. It does this by traversing the
* list and freeing the content and the node itself for each node in the list.
* It uses a temporary pointer to keep track of the next node before freeing
* the current node. */
void	free_storage(t_glist *storage)
{
	t_glist	*current;

	while (storage)
	{
		current = storage;
		storage = storage->next;
		free(current->content);
		free(current);
	}
}
