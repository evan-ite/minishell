/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:44 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/05 18:23:36 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;

	env = environ;
	if (!env || !*env)
	{
		ft_putstr_fd("Error args env\n", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (1);
}
