/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:36:03 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/03 16:47:02 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/* Reallocating memory for the enviroment plus the new
variables that will be added */
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
	temp = gnl_calloc(j + i + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	return (temp);
}

/* Bubble sort to sort the environment variables alphabetically */
char	**sort_env(t_meta *meta)
{
	char	**sorted;
	char	*temp;
	int		i;
	int		j;

	sorted = meta->envp;
	i = 0;
	while (sorted[i])
	{
		j = -1;
		while (sorted[++j] && sorted[j + 1])
		{
			if (sorted[j][0] > sorted[j + 1][0])
			{
				temp = ft_strdup(sorted[j]);
				free(sorted[j]);
				sorted[j] = ft_strdup(sorted[j + 1]);
				free(sorted[j + 1]);
				sorted[j + 1] = ft_strdup(temp);
				free(temp);
			}
		}
		i++;
	}
	return (sorted);
}

/* Copy the environment from meta into temp and also alter the
pointer to integer j to the last index that was filled with env */
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

/* If an exported identifier already exists, it will be replaced */
int	replace_var(int i, char **temp, t_node *node)
{
	int	j;
	int	equal_i;

	equal_i = 0;
	while (node->args[i][equal_i] && node->args[i][equal_i] != '=')
		equal_i++;
	if (!node->args[i][equal_i])
		return (1);
	j = 0;
	while (temp[j])
	{
		if (!ft_strncmp(temp[j], node->args[i], equal_i + 1))
		{
			free(temp[j]);
			temp[j] = ft_strdup(node->args[i]);
			return (1);
		}
		j++;
	}
	return (0);
}
