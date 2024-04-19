/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:34 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/19 15:46:43 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	get_home(t_meta *meta);

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
	else
	{
		if (chdir(meta->envp[get_home(meta)] + 5) != 0)
		{
			ft_putstr_fd("Error cd\n", STDERR_FILENO);
			return (-1);
		}
		return (0);
	}
}

static int	get_home(t_meta *meta)
{
	int	i;

	i = 0;
	while (meta->envp[i])
	{
		if (!ft_strncmp(meta->envp[i], "HOME", 4))
			return (i);
		i++;
	}
	exit_error("HOME isn't set", NULL, 1, meta);
	return (-1);
}
