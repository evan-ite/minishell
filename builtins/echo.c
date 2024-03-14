/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:37 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/14 13:34:25 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int	ft_echo(char **args)
{
	int	i;

	if (!args || !*args)
		return (-1);
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
