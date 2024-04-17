/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:11:41 by evan-ite          #+#    #+#             */
/*   Updated: 2023/12/07 12:48:35 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n)
	{
		c1 = s1[i];
		c2 = s2[i];
		if (c1 != c2 || (!s1[i] || !s2[i]))
			return ((int)c1 - c2);
		i++;
	}
	return (0);
}
