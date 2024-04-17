/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:49:40 by evan-ite          #+#    #+#             */
/*   Updated: 2023/11/23 17:26:23 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = (char *)malloc(len * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i == (int)ft_strlen(s1))
			j = 0;
		if (i < (int)ft_strlen(s1))
			newstr[i] = s1[j];
		else
			newstr[i] = s2[j];
		i++;
		j++;
	}
	return (newstr);
}
