/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:17:30 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:37:02 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static int	inset(char c, char const *set)
{
	int	cinset;
	int	i;

	i = 0;
	cinset = 0;
	while (set[i])
	{
		if (set[i] == c)
			cinset = 1;
		i++;
	}
	return (cinset);
}

static int	find_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start])
	{
		if (inset(s1[start], set))
			start++;
		else
			break ;
	}
	return (start);
}

static int	find_end(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (end >= 0)
	{
		if (inset(s1[end], set))
			end--;
		else
			break ;
	}
	return (end + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		start;
	int		end;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	len = end - start;
	if (len < 0)
		len = 0;
	newstr = ft_substr(s1, start, len);
	return (newstr);
}
