#include "header.h"
#include "gnl/get_next_line.h"

int how_line_in_file(char *file)
{
	int size;
	char *str;
	int fd;

	size = 0;
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		exit((perror("Error: "), 1));
	str = get_next_line(fd);
	while (str)
	{
		size++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return size;
}

char **fill_content(char *file, int *size)
{
	char **map;
	int fd;
	char *line;
	int i;

	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		exit((perror("Error: "), 1));
	i = 0;
	*size = how_line_in_file(file);
	map = malloc((*size + 1) * sizeof(char *));
	if (!map)
		exit ((write (2, "malloc failed\n", 14), 1));
	line = get_next_line(fd);
	while (line)
	{
		map[i] = ft_strdup(line);
		if (!map[i])
			exit ((free_all(map), write (2, "malloc failed\n", 14), 1));
		free (line);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return map;
}

