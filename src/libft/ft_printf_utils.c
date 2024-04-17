/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:39:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/10 15:05:11 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *str)
{
	int	error_check;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	error_check = ft_putstr_fd(str, 1);
	if (error_check)
		return (ft_strlen(str));
	return (-1);
}

int	print_int(int i)
{
	int	count;

	count = 0;
	count = ft_putnbr_fd(i, 1);
	if (count < 0)
		return (-1);
	return (count);
}

int	print_pointer(unsigned long n)
{
	int	count;
	int	write_check;

	if (n == 0)
	{
		write_check = write(1, "(nil)", 5);
		if (write_check < 5)
			return (-1);
		return (5);
	}
	write_check = write(1, "0x", 2);
	count = ft_putnbr_base_fd(1, n, "0123456789abcdef");
	if (write_check < 2 || count < 0)
		return (-1);
	return (count + 2);
}

int	print_unsigned(unsigned int n)
{
	int	count;

	count = ft_putnbr_fd(n, 1);
	if (count < 0)
		return (-1);
	return (count);
}

int	print_hex(unsigned int n, int uppercase)
{
	int	count;

	if (!uppercase)
		count = ft_putnbr_base_fd(1, n, "0123456789abcdef");
	else
		count = ft_putnbr_base_fd(1, n, "0123456789ABCDEF");
	if (count < 0)
		return (-1);
	return (count);
}
