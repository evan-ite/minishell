/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:04:13 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:36:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	else if (ft_strncmp(little, "", ft_strlen(little)) == 0)
		return ((char *)little);
	while (big[i] && len > 0)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (little[j] && big[i + j] == little[j] && i + j < len)
				j++;
			if (i + j <= len && little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
