/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:58 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:27:56 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static size_t	lenword(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static size_t	countword(const char *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	word;

	count = 0;
	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (count == 0)
			{
				word++;
				count = 1;
			}
		}
		else
			count = 0;
		i++;
	}
	return (word);
}

static char	**ft_free(char **ptr, size_t index)
{
	size_t	i;

	i = 0;
	while (i <= index)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	**ft_cut(char **ptr, size_t colom, char const *s, char c)
{
	size_t	i;
	size_t	lenwords;
	size_t	line;

	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		lenwords = lenword(s + i, c);
		if (lenwords != 0)
		{
			ptr[colom] = malloc((lenwords + 1) * sizeof(char));
			if (!ptr[colom])
				return (ft_free(ptr, colom));
			line = 0;
			while (line < lenwords && s[i])
				ptr[colom][line++] = s[i++];
			ptr[colom][line] = '\0';
			colom++;
		}
	}
	ptr[colom] = NULL;
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	words;

	if (!s)
		return (NULL);
	words = countword(s, c);
	ptr = malloc((words + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ft_cut(ptr, 0, s, c));
}
