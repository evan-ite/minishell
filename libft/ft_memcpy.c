/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:13:26 by evan-ite          #+#    #+#             */
/*   Updated: 2023/11/24 15:20:28 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s_ptr;
	unsigned char		*d_ptr;
	size_t				i;

	s_ptr = src;
	d_ptr = dest;
	if (!d_ptr && !s_ptr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return (dest);
}
