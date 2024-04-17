/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:23:26 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:36:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	int				len;
	unsigned int	i;

	len = ft_strlen(s);
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
