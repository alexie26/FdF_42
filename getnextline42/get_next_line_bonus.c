/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:32:22 by roalexan          #+#    #+#             */
/*   Updated: 2024/12/07 17:54:42 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*gnl_calloc(unsigned int count, unsigned int size)
{
	void			*pointer;
	unsigned char	*p;

	pointer = malloc(count * size);
	if (!pointer)
		return (NULL);
	p = pointer;
	while (size--)
		*p++ = '\0';
	return (pointer);
}

char	*read_bytes(int fd, char *full_read)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		store;

	store = BUFFER_SIZE;
	if (!full_read)
		full_read = gnl_strdup("");
	if (!full_read)
		return (NULL);
	store = 1;
	while (store > 0)
	{
		store = read(fd, buffer, BUFFER_SIZE);
		if (store < 0)
			return (free(full_read), NULL);
		buffer[store] = '\0';
		temp = gnl_strjoin(full_read, buffer);
		free(full_read);
		if (!temp)
			return (NULL);
		full_read = temp;
		if (gnl_strchr(full_read, '\n'))
			break ;
	}
	return (full_read);
}

char	*ft_extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = gnl_substr(buffer, 0, i + 1);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*ft_next(char *buffer)
{
	char	*newline_pos;
	char	*line;

	newline_pos = gnl_strchr(buffer, '\n');
	if (!newline_pos)
	{
		free(buffer);
		return (NULL);
	}
	line = gnl_strdup(newline_pos + 1);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_bytes(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_extract_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	// atexit(leaks);
// 	fd = open("text.txt", O_RDONLY);
// 	// if (fd < 0)
// 	// {
// 	//     perror("Error opening file");
// 	//     return (1);
// 	// }
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		if (line == NULL)
// 		{
// 			printf("NULL\n");
// 		}
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
