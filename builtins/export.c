/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:48 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 14:52:10 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static char	**realloc_env(t_node *node, t_meta *meta)
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
	temp = gnl_calloc(j + i + 1, sizeof(char*));
	if (!temp)
		return (NULL);
	return (temp);
}

static void	export_no_args(t_meta *meta)
{
	int		i;
	char	**temp;

	i = 0;
	while (meta->envp[i])
	{
		// printf("TEST %i\n", i);
		if (ft_strlen(meta->envp[i]) > 1)
		{
			temp = ft_split(meta->envp[i], '=');
			if (!temp)
				exit_error(ERR_MEM, NULL, 1, meta);
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(temp[0], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			printf("TEST %i\n", i);
			ft_putstr_fd(temp[1], STDOUT_FILENO); // SEGFAULT
			ft_putstr_fd("\"\n", STDOUT_FILENO);
			free(temp);
		}
		i++;
	}
}

void	copy_env(char **temp, int *j, t_meta *meta)
{
	*j = 0;
	while (meta->envp[*j])
	{
		temp[*j] = ft_strdup(meta->envp[*j]);
		if (!temp[*j])
			exit_error(ERR_MEM, NULL, 1, meta);
		(*j)++;
	}
}

int	ft_export(t_node *node, t_meta *meta)
{
	char	**temp;
	int		i;
	int		j;

	if (!node->args || !*(node->args) || !meta->envp || !(*meta->envp))
		exit_error("Export error", NULL, 1, meta);
	if (!node->args[1])
		export_no_args(meta);
	else
	{
		temp = realloc_env(node, meta);
		copy_env(temp, &j, meta);
		i = 1;
		while (node->args[i])
		{
			// HANDLE INVALID VAR NAMES OR SPACES AROUND EQUAL SIGN
			// OR WHAT IF THERES NO EQUAL SIGN, IT SHOWS IN EXPORT BUT NOT IN ENV
			temp[j] = ft_strdup(node->args[i]);
			if (!temp[j])
				exit_error(ERR_MEM, NULL, 1, meta);
			j++;
			i++;
		}
		temp[j] = NULL;
		meta->envp = temp;
	}
	return (0);
}
