/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:43:50 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/15 11:10:40 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s1[i] ||  s2[i])
		return (-1);
	return (0);
}
