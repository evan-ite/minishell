/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:55:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/01/10 11:28:40 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	check_format(const char *format, va_list args)
{
	int		char_count;

	char_count = 0;
	if (*format == '\0')
	{
		va_end(args);
		return (-1);
	}
	else if (*format == 'c')
		char_count += ft_putchar_fd(va_arg(args, int), 1);
	else if (*format == 's')
		char_count += print_string(va_arg(args, char *));
	else if (*format == 'p')
		char_count += print_pointer(va_arg(args, unsigned long));
	else if (*format == 'i' || *format == 'd')
		char_count += print_int(va_arg(args, int));
	else if (*format == '%')
		char_count += ft_putchar_fd('%', 1);
	else if (*format == 'u')
		char_count += print_unsigned(va_arg(args, unsigned int));
	else if (*format == 'x')
		char_count += print_hex(va_arg(args, unsigned int), 0);
	else if (*format == 'X')
		char_count += print_hex(va_arg(args, unsigned int), 1);
	return (char_count);
}

int	ft_printf(const char *format, ...)
{
	int		char_count;
	int		temp;
	va_list	args;

	va_start(args, format);
	char_count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			temp = check_format(++format, args);
			if (temp < 0)
				return (-1);
			char_count += temp;
		}
		else
		{
			if (write(1, format, 1) < 0)
				return (-1);
			char_count++;
		}
		format++;
	}
	va_end(args);
	return (char_count);
}
