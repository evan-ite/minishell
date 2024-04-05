/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:34 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/05 18:23:23 by evan-ite         ###   ########.fr       */
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
		if (!chdir(path))
			return (1);
		else
		{
			ft_putstr_fd("Error cd\n", STDERR_FILENO);
			return (-1);
		}
	}
	else
	{
		if (!chdir("/"))
			return (1);
		else
		{
			ft_putstr_fd("Error cd\n", STDERR_FILENO);
			return (-1);
		}
	}
}
