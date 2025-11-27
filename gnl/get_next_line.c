/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:52:34 by oobbad            #+#    #+#             */
/*   Updated: 2025/02/22 18:44:27 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*renew_saved(char *saved)
{
	size_t	i;
	size_t	j;
	char	*new_saved;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = malloc((ft_strlen(saved) - i + 1) * sizeof(char));
	if (!new_saved)
		return (NULL);
	j = 0;
	i++;
	while (saved[i])
		new_saved[j++] = saved[i++];
	new_saved[j] = '\0';
	free(saved);
	return (new_saved);
}

char	*cut_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_buffer(int fd, char *saved)
{
	int		read_byte;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && find_line(saved) == -1)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(saved);
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		saved = ft_strjoin(saved, buffer);
		if (!saved)
			return (NULL);
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_buffer(fd, saved);
	line = cut_line(saved);
	saved = renew_saved(saved);
	return (line);
}
// int main(void) {
//     int fd;
//     char *line;
//     fd = open("map.ber", O_RDONLY);
//     if (fd == -1) {
//         perror("Error opening file");
//         return 1;
//     }
// 	line = get_next_line(fd);
// 	while (line)
// 	{
//         printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
//     close(fd);
//     return 0;
// }
