/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:53 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/08 16:46:14 by evan-ite         ###   ########.fr       */
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
		j = 1;
		while (node->args[j])
		{
			if (!ft_strcmp(var[0], node->args[j]))
			{
				printf("FOUND MATCH arg = %s, var = %s\n", node->args[j], meta->envp[i]);
				free(meta->envp[i]);
				meta->envp[i] = ft_strdup(" ");
			}
			j++;
		}
		free(var);
		i++;
	}
	return (1);
}
