/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:48 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/16 17:31:07 by evan-ite         ###   ########.fr       */
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

static char	**sort_env(t_meta *meta)
// Bubble sort to sort the environment variables alphabetically
{
	char	**sorted;
	char	*temp;
	int		i;
	int		j;

	sorted = meta->envp;
	i = 0;
	while (sorted[i])
	{
		j = 0;
		while (sorted[j] && sorted[j + 1])
		{
			if (sorted[j][0] > sorted[j + 1][0])
			{
				temp = ft_strdup(sorted[j]);
				sorted[j] = ft_strdup(sorted[j + 1]);
				sorted[j + 1] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

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

static int	check_identifiers(int i, t_node *node, t_meta *meta)
{
	int	j;

	if (!ft_isalpha(node->args[i][0]))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(node->args[i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		meta->exit_code = 1;
		return (1);
	}
	j = 0;
	while (node->args[i][j])
	{
		if (node->args[i][j] == '=')
			break ;
		if (!ft_isalnum(node->args[i][j]))
		{
			ft_putstr_fd("export: '", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			meta->exit_code = 1;
			return (1);
		}
		j++;
	}
	return (0);
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
			check_identifiers(i, node, meta);
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
