/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:09:37 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 14:36:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:10:24 by evan-ite          #+#    #+#             */
/*   Updated: 2023/11/24 15:39:03 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "libft.h"

static int	print_nbr(int fd, unsigned long nb, char *base, int *write_check)
// Prints numbers according to base.
{
	char			nbr;
	unsigned long	base_count;
	int				count;

	base_count = ft_strlen(base);
	count = 0;
	if (nb >= base_count)
	{
		count += print_nbr(fd, nb / base_count, base, write_check);
		nbr = base[nb % base_count];
		*write_check += write(fd, &nbr, 1);
		count++;
	}
	else
	{
		nbr = base[nb];
		*write_check += write(fd, &nbr, 1);
		count++;
	}
	return (count);
}

static int	duplicate_counter(char *base)
// Checks duplicates in base string.
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base [j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	valid_base(char *base)
// Checks if base string is valid.
{
	int	i;

	i = 0;
	if (ft_strlen(base) <= 1)
		return (0);
	else if (duplicate_counter(base))
		return (0);
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_putnbr_base_fd(int fd, unsigned long nb, char *base)
{
	int	count;
	int	write_check;

	count = 0;
	write_check = 0;
	if (valid_base(base))
	{
		count += print_nbr(fd, nb, base, &write_check);
		if (count < 0 || write_check != count)
			return (-1);
		return (count);
	}
	else
		return (count);
}
