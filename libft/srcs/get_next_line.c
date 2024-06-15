/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:25:47 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 16:51:20 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** "main" function of the project, reads a line from a file descriptor and
* returns it as a string. It uses a static variable 'storage' to keep track
* of the remaining characters from the file descriptor that have not yet been
* returned as a line. */
char	*get_next_line(int fd)
{
	static t_glist	*storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	read_and_store(fd, &storage);
	if (storage)
	{
		extract_line_to_print(storage, &line);
		remove_printed_line(&storage);
		if (line && line[0] == '\0')
		{
			free_storage(storage);
			storage = 0;
			free(line);
			line = 0;
		}
	}
	return (line);
}

/** Function that uses read() to store characters. It reads characters from
* the file descriptor into a buffer 'chars_read', then adds the buffer to
* the end of 'storage'. It continues to do this until it encounters a
* newline character or reaches the end of the file. The buffer is then freed.*/
void	read_and_store(int fd, t_glist **storage)
{
	ssize_t	n_read;
	char	*chars_read;

	chars_read = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chars_read)
		return ;
	n_read = BUFFER_SIZE;
	while (new_line_not_present(*storage) && n_read == BUFFER_SIZE)
	{
		n_read = read(fd, chars_read, BUFFER_SIZE);
		if (n_read == -1)
			break ;
		chars_read[n_read] = '\0';
		add_to_storage(storage, chars_read, n_read);
	}
	free(chars_read);
}

/** Adds the contents of the buffer to the end of 'storage'. First it creates
* a new node, then copies the buffer into the new node, and adds the new node
* to the end of the static structure 'storage'. */
void	add_to_storage(t_glist **storage, char *chars_read, int n_read)
{
	t_glist	*last;
	t_glist	*new_node;
	ssize_t	i;

	new_node = (t_glist *)malloc(sizeof(t_glist));
	if (!new_node)
		return ;
	new_node->next = 0;
	new_node->content = (char *)malloc(sizeof(char) * (n_read + 1));
	if (!(new_node->content))
		return ;
	i = 0;
	while (chars_read[i] && i < n_read)
	{
		new_node->content[i] = chars_read[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*storage == 0)
	{
		*storage = new_node;
		return ;
	}
	last = ft_lst_last(*storage);
	last->next = new_node;
}

/** Extracts from the stored characters to form a line. It allocates memory
* for the line, then copies characters from 'storage' into the line until it
* encounters a newline character or reaches the end of 'storage'. */
void	extract_line_to_print(t_glist *storage, char **line)
{
	int	i;
	int	j;

	if (!storage)
		return ;
	malloc_line(line, storage);
	if (!(*line))
		return ;
	j = 0;
	while (storage)
	{
		i = 0;
		while (storage->content[i])
		{
			if (storage->content[i] == '\n')
			{
				(*line)[j++] = storage->content[i];
				break ;
			}
			(*line)[j++] = storage->content[i++];
		}
		storage = storage->next;
	}
	(*line)[j] = '\0';
}

/** Removes the just printed line from 'storage'. It does this by creating a
* new node, copying the remaining characters from the last node of 'storage'
* into the new node, freeing 'storage', and then setting 'storage' to the
* new node. */
void	remove_printed_line(t_glist **storage)
{
	t_glist	*clean_node;
	t_glist	*last_node;
	int		i;
	int		j;

	clean_node = (t_glist *)malloc(sizeof(t_glist));
	if (!(*storage) || !clean_node)
		return ;
	clean_node->next = 0;
	last_node = ft_lst_last(*storage);
	i = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content && last_node->content[i] == '\n')
		i++;
	clean_node->content = (char *)malloc(sizeof(char)
			* (ft_strlen_gnl(last_node->content) - i + 1));
	if (!(clean_node->content))
		return ;
	j = 0;
	while (last_node->content[i])
		clean_node->content[j++] = last_node->content[i++];
	clean_node->content[j] = '\0';
	free_storage(*storage);
	*storage = clean_node;
}
