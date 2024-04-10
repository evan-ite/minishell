/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:34 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 12:02:05 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_cd(char **args)
{
	char *path;

	if (!*args || !args)
	{
		ft_putstr_fd("No args cd\n", STDERR_FILENO);
		return (-1);
	}
	if (args[1])
	{
		path = args[1];
		if (chdir(path) != 0)
		{
			ft_putstr_fd("Error cd\n", STDERR_FILENO);
			return (-1);
		}
		return (0);
	}
	else
	{
		if (chdir("/") != 0)
		{
			ft_putstr_fd("Error cd\n", STDERR_FILENO);
			return (-1);
		}
		return (0);
	}
}
