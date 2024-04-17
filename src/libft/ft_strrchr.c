/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:32:39 by evan-ite          #+#    #+#             */
/*   Updated: 2023/11/22 13:03:58 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	ptr = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			ptr = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	else if (ptr != NULL)
		return ((char *)ptr);
	else
		return (NULL);
}
