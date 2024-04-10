/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:53 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 12:05:22 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_unset(t_node *node, t_meta *meta)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	while (meta->envp[i])
	{
		var = ft_split(meta->envp[i], '=');
		if (!var)
			exit_error(ERR_MEM, NULL, 1, meta);
		j = 0;
		while (node->args[++j])
		{
			if (!ft_strcmp(var[0], node->args[j]))
			{
				free(meta->envp[i]);
				meta->envp[i] = ft_strdup(" ");
				if (!meta->envp[i])
					exit_error(ERR_MEM, NULL, 1, meta);
			}
		}
		free(var);
		i++;
	}
	return (0);
}
