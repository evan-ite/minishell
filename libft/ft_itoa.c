/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:19:49 by evan-ite          #+#    #+#             */
/*   Updated: 2023/12/14 11:27:06 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	print_nbr(char *str, int n, int strlen)
{
	char	num;

	if (n > 9)
	{
		print_nbr(str, n / 10, strlen - 1);
		num = n % 10 + 48;
		str[strlen] = num;
	}
	else if (n >= 0 && n <= 9)
	{
		num = n + 48;
		str[strlen] = num;
	}
	else
	{
		if (n == -2147483648)
		{
			str[strlen] = '8';
			n = -214748364;
			strlen -= 1;
		}
		str[0] = '-';
		n *= -1;
		print_nbr(str, n, strlen);
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		strlen;

	strlen = count_digits(n);
	str = (char *)malloc(sizeof(char) * strlen + 1);
	if (!str)
		return (NULL);
	print_nbr(str, n, strlen - 1);
	str[strlen] = '\0';
	return (str);
}
