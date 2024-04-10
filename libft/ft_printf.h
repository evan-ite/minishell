/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:27:06 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/10 16:45:29 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	print_string(char *str);
int	print_int(int i);
int	print_pointer(unsigned long n);
int	print_unsigned(unsigned int n);
int	print_hex(unsigned int n, int uppercase);

#endif
