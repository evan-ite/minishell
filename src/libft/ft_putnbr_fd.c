/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:10:24 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/10 14:49:24 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	put_digit_save(long n, int fd, int *write_check)
{
	char	num;
	int		count;

	count = 0;
	if (n >= 0)
	{
		if (n > 9)
		{
			count += put_digit_save(n / 10, fd, write_check);
			num = n % 10 + '0';
		}
		else
			num = n + '0';
		count++;
		*write_check += write(fd, &num, 1);
	}
	else
	{
		*write_check += write(fd, "-", 1);
		count += put_digit_save(-n, fd, write_check) + 1;
	}
	return (count);
}

int	ft_putnbr_fd(long n, int fd)
{
	int	count;
	int	write_check;

	write_check = 0;
	count = put_digit_save(n, fd, &write_check);
	if (count < 0 || write_check != count)
		return (-1);
	return (count);
}
