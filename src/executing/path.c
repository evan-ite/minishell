/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:05:36 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/19 12:48:57 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

static char	*create_full_path(char *path, char *cmnd, t_meta *meta)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin("/", cmnd);
	if (!temp)
		exit_error(ERR_MEM, NULL, 1, meta);
	result = ft_strjoin(path, temp);
	free(temp);
	if (!result)
		exit_error(ERR_MEM, NULL, 1, meta);
	return (result);
}

static void	find_path(char *path, t_node *node, t_meta *meta)
{
	int		i;
	char	**path_options;

	path_options = ft_split(path, ':');
	if (!path_options)
		exit_error(ERR_MEM, NULL, 1, meta);
	i = 0;
	while (path_options[i])
	{
		node->path = create_full_path(path_options[i], node->command, meta);
		if (access(node->path, X_OK) == 0)
			break ;
		free(node->path);
		node->path = NULL;
		i++;
	}
	free_array((void **)path_options, -1);
	return ;
}

void	get_path(t_meta *meta, t_node *node)
{
	char	*paths;

	if (ft_strchr(node->command, '/'))
	{
		node->path = ft_strdup(node->command);
		if (!node->path)
			exit_error(ERR_MEM, NULL, 1, meta);
	}
	paths = ft_strdup(getenv("PATH"));
	if (!node->path)
		find_path(paths, node, meta);
	if (!node->path)
	{
		free(paths);
		exit_error(ERR_CMND, node->command, 127, meta);
	}
	free(paths);
	return ;
}
