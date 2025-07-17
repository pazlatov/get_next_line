/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pzlatov <pzlatov@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:26:23 by pzlatov       #+#    #+#                 */
/*   Updated: 2025/02/06 14:43:13 by pzlatov       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_buf(char **line, char **buffer)
{
	if (line && *line)
		free(*line);
	if (line)
		*line = NULL;
	if (buffer && *buffer)
		free(*buffer);
	if (buffer)
		*buffer = NULL;
	return (NULL);
}

static char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_new_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free_buf(&stash, NULL));
	new_stash = malloc((ft_strlen(stash) - i) * sizeof(char));
	if (!new_stash)
		return (free_buf(&stash, NULL));
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free_buf(&stash, NULL);
	if (new_stash[0] == '\0')
		return (free_buf(&new_stash, NULL));
	return (new_stash);
}

static char	*ft_read_file(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_buf(&stash, NULL));
	bytes_read = 1;
	while (bytes_read > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_buf(&stash, NULL), free_buf(&buffer, NULL));
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = ft_strjoin(stash, buffer);
		free_buf(&stash, NULL);
		if (!temp)
			return (free_buf(NULL, &buffer));
		stash = temp;
	}(bytes_read == -1
	return (free_buf(NULL, &buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buf(&stash, NULL));
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	if (!line)
	{
		free_buf(&stash, NULL);
		return (NULL);
	}
	stash = ft_new_stash(stash);
	return (line);
}
