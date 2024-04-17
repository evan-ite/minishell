/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:45:07 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:36:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_strlen(src) + ft_strlen(dest);
	while (i < size && dest[i] != '\0')
		i++;
	if (i == size || size <= 0)
		return (size + ft_strlen(src));
	j = 0;
	while (i < size - 1 && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (len);
}
