/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:48 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/03 15:28:30 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/* If export is called without arguments a list of declared
variables is printed in a specific format */
static void	export_no_args(t_meta *meta)
{
	int		i;
	char	**temp;
	char	**sorted;

	sorted = sort_env(meta);
	i = 0;
	while (sorted[i])
	{
		if (ft_strlen(sorted[i]) > 1)
		{
			temp = ft_split(sorted[i], '=');
			if (!temp)
				exit_error(ERR_MEM, NULL, 1, meta);
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(temp[0], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(temp[1], STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
			free_array((void **)temp, -1);
		}
		i++;
	}
}

/* Checks if the identifier of the new environment variable
is valid. If identifier is not valid returns 0, on succes returns 1 */
static int	check_identifiers(int i, t_node *node, t_meta *meta)
{
	int	j;

	if (!ft_isalpha(node->args[i][0]))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(node->args[i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		meta->exit_code = 1;
		return (0);
	}
	j = -1;
	while (node->args[i][++j])
	{
		if (node->args[i][j] == '=')
			break ;
		if (!ft_isalnum(node->args[i][j]))
		{
			ft_putstr_fd("export: '", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			meta->exit_code = 1;
			return (0);
		}
	}
	return (1);
}

/* Checks if the arguments that need to be exported are valid and
if so they will be added to meta->envp*/
static void	export_args(t_node *node, t_meta *meta)
{
	int		i;
	int		j;
	char	**temp;

	temp = realloc_env(node, meta);
	copy_env(temp, &j, meta);
	i = 1;
	while (node->args[i])
	{
		if (check_identifiers(i, node, meta))
		{
			if (!replace_var(i, temp, node))
			{
				temp[j] = ft_strdup(node->args[i]);
				if (!temp[j])
					exit_error(ERR_MEM, NULL, 1, meta);
				j++;
			}
		}
		i++;
	}
	temp[j] = NULL;
	free_array((void **)meta->envp, -1);
	meta->envp = temp;
}

int	ft_export(t_node *node, t_meta *meta)
{
	if (!node->args || !*(node->args) || !meta->envp || !(*meta->envp))
		exit_error("Export error", NULL, 1, meta);
	if (!node->args[1])
		export_no_args(meta);
	else
		export_args(node, meta);
	return (0);
}
