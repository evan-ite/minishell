/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:34 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/02 17:11:50 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/parsing.h"

static int	go_home(t_meta *meta);

/*
builtin function that changes the directory to the specified location.
If no argument is given, then cd will automatically go to the HOME directory,
as determined by the envars. If no home directory is set, an error will be given
*/
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
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			meta->exit_code = 1;
		}
		return (0);
	}
	return (go_home(meta));
}

/*
This function extracts the HOME path from envars and sets the working directory
to there*/
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
