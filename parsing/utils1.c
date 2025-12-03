#include "../header.h"


int ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 && !s2))
		return (0);
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) 
		&& ((unsigned char)s2[i] || (unsigned char)s1[i]))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool check_if_double_id(t_textures *tex, char *str)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (tex[i].id && !ft_strcmp(tex[i].id, str))
			return (true);
		i++;
	}
	return false;
}

bool check_line_is_one(char *line, int *begin_map)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return (false);
		i++;
	}
	if (begin_map)
		*begin_map = 1;
	return true;

}


bool check_if_malloc_fail(t_textures* tex)
{
	int i;
	
	i = 0; 
	while (i < 4)
	{
		if (!tex[i].id || !tex->path)
			return true;
		i++;
	}
	return false;
}