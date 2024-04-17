/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:33 by evan-ite          #+#    #+#             */
/*   Updated: 2023/11/24 15:20:37 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s_ptr;
	unsigned char		*d_ptr;
	size_t				i;

	s_ptr = src;
	d_ptr = dest;
	i = 0;
	if (!d_ptr && !s_ptr)
		return (NULL);
	if (d_ptr > s_ptr)
	{
		while (n-- > 0)
			d_ptr[n] = s_ptr[n];
	}
	else
	{
		while (i < n)
		{
			d_ptr[i] = s_ptr[i];
			i++;
		}
	}
	return (dest);
}
