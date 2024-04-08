/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:48 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/08 17:22:01 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	**realloc_env(t_node *node, t_meta *meta)
{
	char	**temp;
	int		i;
	int		j;

	j = 0;
	while (meta->envp[j])
		j++;
	i = 1;
	while (node->args[i])
		i++;
	temp = gnl_calloc(j + i, sizeof(char*));
	if (!temp)
		return (NULL);
	return (temp);
}

int	ft_export(t_node *node, t_meta *meta)
{
	char	**temp;
	int		i;
	int		j;

	// HANDLE EXPORT WITHOUT ARGS
	temp = realloc_env(node, meta);
	j = 0;
	while (meta->envp[j])
	{
		temp[j] = ft_strdup(meta->envp[j]);
		j++;
	}
	i = 1;
	while (node->args[i])
	{
		// HANDLE INVALID VAR NAMES OR SPACES AROUND EQUAL SIGN
		// OR WHAT IF THERES NO EQUAL SIGN, IT SHOWS IN EXPORT BUT NOT IN ENV
		temp[j] = ft_strdup(node->args[i]);
		j++;
		i++;
	}
	meta->envp = temp;
	return (1);
}
