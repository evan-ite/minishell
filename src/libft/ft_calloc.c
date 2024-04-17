/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:08:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/07 12:36:59 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (!(nmemb == 0) && !(size == 0))
	{
		if (nmemb > SIZE_MAX / size || nmemb > INT_MAX / size)
			return (NULL);
		array = malloc(nmemb * size);
		if (!array)
			return (NULL);
		ft_bzero(array, nmemb * size);
		return (array);
	}
	return (NULL);
}
