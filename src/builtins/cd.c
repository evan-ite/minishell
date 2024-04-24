/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:34 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/24 16:07:06 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

static int	go_home(t_meta *meta);

int	ft_cd(char **args, t_meta *meta)
{
	char	*path;

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
	return (go_home(meta));
}

static int	go_home(t_meta *meta)
{
	char	*home;

	home = get_envar(meta, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: Home not set\n", STDERR_FILENO);
		return (0);
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("Error cd\n", STDERR_FILENO);
		return (0);
	}
	return (EXIT_SUCCESS);
}
