/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:44 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/03 23:17:46 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/*
prints all set environment variables out*/
int	ft_env(t_meta *meta)
{
	int	i;

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
