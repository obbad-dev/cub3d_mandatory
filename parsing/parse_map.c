#include "../header.h"

bool valid_caracter(char c, char *dir)
{
	static int one_time;

	if (c == '1' || c == '0')
		return true;
	else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E') && one_time == 0)
	{
		
		*dir = c;
		return (one_time++, true);
	}
	else
		return false;
}

bool first_last_is_one(char *line)
{
	int j;
	int size_line;

	j = 0;
	size_line = ft_strlen(line);
	skip_spaces(line, &j);
	if (line[j] != '1' || line[size_line - 1] != '1')
		return false;
	else
		return true;
}
bool surronded_by_wall(char **map, int size)
{
	int i;

	i = 0;
	while (map && map[i])
	{
		if ((i == 0 || i == size -1) && !check_line_is_one(map[i], NULL))
		{
			ft_print_error("Error\nLine invalide\n");
			return false;
		}
		else if (!first_last_is_one(map[i]))
		{
			ft_print_error("Error\nLine invalide\n");
			return false;
		}
		i++;
	}
	return true;
}

int count_line_map(char **content)
{
	int i;

	i = 0;
	while(content && content[i])
	{
		i++;
	}
	return i;
}

bool check_map(char **map, t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (!valid_caracter(map[i][j], &data->direction) && !ft_isspace(map[i][j]))
				return ( write(2, "invalide character\n", 19), false);
			j++;
		}
		i++;
	}
	data->rows = count_line_map(map);
	if (!surronded_by_wall(map, data->rows))
		return false;
	else
		return true;
}

bool fill_map(char **content, t_data *data)
{
	int i;

	i = 0;
	data->map = malloc((count_line_map(content) + 1) * sizeof(char *));
	if (!data->map)
		return (ft_print_error("malloc fail\n"), false);
	while (content && content[i])
	{
		data->map[i] = ft_strdup(content[i]);
		if (!data->map[i])
			return (free_all(data->map), ft_print_error("malloc fail\n"), false);
		i++;
	}
	data->map[i] = NULL;
	return true;
}

void parse_map(char **content, t_data *data)
{

	if (!fill_map(content + data->begin_map, data))
		exit((free_texture(data->tex, content), 1));
	free_all(content);
	if (!check_map(data->map, data))
		exit((free_texture(data->tex, data->map), 1));
}