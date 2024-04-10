/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:44 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 12:02:26 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_env(t_meta *meta)
{
	int			i;

	if (!meta->envp || !*(meta->envp))
	{
		ft_putstr_fd("Error args env\n", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (meta->envp[i])
	{
		if (ft_strlen(meta->envp[i]) > 1)
		{
			ft_putstr_fd(meta->envp[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
