/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:09:45 by evan-ite          #+#    #+#             */
/*   Updated: 2023/11/30 13:52:16 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	strlen_s;

	if (!s)
		return (NULL);
	strlen_s = ft_strlen(s);
	if (len > strlen_s)
		len = strlen_s;
	if (start > strlen_s)
		len = 0;
	else if (start + len > strlen_s)
		len = strlen_s - start;
	substr = (char *)malloc(len * sizeof(char) + 1);
	if (!substr)
		return (NULL);
	s += start;
	i = 0;
	while (i < len && s[i])
	{
		substr[i] = s[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
