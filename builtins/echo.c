/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:37 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 12:02:14 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"


int	ft_echo(char **args)
{
	int	i;

	if (!args || !*args)
	{
		ft_putstr_fd("No arguments for echo\n", STDERR_FILENO);
		return (-1);
	}
	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
