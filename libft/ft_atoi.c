/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:37:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/06 16:35:09 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *s)
{
	int	sign;
	int	value;

	sign = 1;
	value = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
			value = value * 10 + (*s - '0');
		else
			return (sign * value);
		s++;
	}
	return (sign * value);
}
