/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:47:55 by dherszen          #+#    #+#             */
/*   Updated: 2024/01/23 16:39:12 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** "main" function of bonus part the project, reads a line from each file
* descriptor and returns it as a string. It uses a static variable 'storage'
* to keep track of the remaining characters from each file descriptor that
* have not yet been returned as a line. */
char	*get_next_line_fd(int fd)
{
	static t_glist	*storage[FD_SIZE];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_SIZE)
		return (0);
	line = 0;
	read_and_store(fd, &storage[fd]);
	if (storage[fd])
	{
		extract_line_to_print(storage[fd], &line);
		remove_printed_line(&storage[fd]);
		if (line && line[0] == '\0')
		{
			free_storage(storage[fd]);
			storage[fd] = 0;
			free(line);
			line = 0;
		}
	}
	return (line);
}
