/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:03:40 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:37:17 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			counter++;
			while (*s && *s != c)
				s++;
		}
	}
	return (counter);
}

static int	allocate_substr(char **array, const char *start, const char *end)
{
	*array = ft_substr(start, 0, end - start);
	if (!*array)
		return (0);
	return (1);
}

static int	create_substrs(char **array, char const *s, char c)
{
	char	*start;
	int		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			if (!allocate_substr(&array[i], start, s))
				return (0);
			i++;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;

	if (!*s || !s)
	{
		array = (char **)malloc(sizeof(char *));
		if (!array)
			return (NULL);
		array[0] = NULL;
		return (array);
	}
	words = word_count(s, c);
	array = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!array)
		return (NULL);
	if (create_substrs(array, s, c))
	{
		array[words] = NULL;
		return (array);
	}
	while (words > 0)
		free(array[--words]);
	free(array);
	return (NULL);
}
