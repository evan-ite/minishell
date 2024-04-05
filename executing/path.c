/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:05:36 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/05 16:06:18 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static char	*get_options(t_meta *meta)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (meta->envp[i])
	{
		if (!ft_strncmp(meta->envp[i], "PATH=", 5))
		{
			path = ft_substr(meta->envp[i], 5, ft_strlen(meta->envp[i]));
			if (!path)
				exit_error(ERR_MEM, NULL, 5, meta->cmnd_lst);
			break ;
		}
		i++;
	}
	if (!path)
		exit_error("Could not find PATH", NULL, 3, meta->cmnd_lst);
	return (path);
}

static char	*create_full_path(char *path, char *cmnd, t_meta *meta)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin("/", cmnd);
	if (!temp)
		exit_error(ERR_MEM, NULL, 5, meta->cmnd_lst);
	result = ft_strjoin(path, temp);
	free(temp);
	if (!result)
		exit_error(ERR_MEM, NULL, 5, meta->cmnd_lst);
	return (result);
}

static void	find_path(char *path, t_node *node, t_meta *meta)
{
	int		i;
	char	**path_options;

	path_options = ft_split(path, ':');
	if (!path_options)
		exit_error(ERR_MEM, NULL, 5, meta->cmnd_lst);
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
	free_array(path_options);
	return ;
}

void	get_path(int i, t_meta *meta, t_node *node)
{
	char	*paths;

	if (ft_strchr(node->command, '/'))
	{
		node->path = ft_strdup(node->command);
		if (!node->path)
			exit_error(ERR_MEM, NULL, 5, meta->cmnd_lst);
	}
	paths = get_options(meta);
	if (!node->path)
		find_path(paths, node, meta);
	if (!node->path)
	{
		free(paths);
		ft_close(meta->pipe[i + 1][0]);
		ft_close(meta->pipe[i + 1][1]);
		exit_error(ERR_CMND, node->command, 2, meta->cmnd_lst);
	}
	free(paths);
	return ;
}
