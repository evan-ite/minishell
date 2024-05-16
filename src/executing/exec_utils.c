/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:29:17 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/16 12:24:54 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

char	*remove_nl(char *line)
{
	int		len;
	char	*temp;

	len = ft_strlen(line);
	temp = NULL;
	if (line[len - 1] == '\n')
		temp = ft_substr(line, 0, len - 1);
	else
		temp = line;
	return (temp);
}

int	firstcheck_builtin(t_node *node, t_meta *meta)
{
	if (!node->command)
		return (EXIT_FAILURE);
	if (!ft_strcmp(node->command, "exit"))
		ft_exit(node, meta);
	else if (!ft_strcmp(node->command, "cd"))
		return (ft_cd(node->args, meta));
	else if (!ft_strcmp(node->command, "export"))
		return (ft_export(node, meta));
	else if (!ft_strcmp(node->command, "unset"))
		return (ft_unset(node, meta));
	return (-1);
}

int	check_builtin(t_node *node, t_meta *meta)
{
	if (!node->command)
		return (EXIT_FAILURE);
	if (!ft_strcmp(node->command, "exit"))
		ft_exit(node, meta);
	else if (!ft_strcmp(node->command, "echo"))
		return (ft_echo(node->args));
	else if (!ft_strcmp(node->command, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(node->command, "cd"))
		return (ft_cd(node->args, meta));
	else if (!ft_strcmp(node->command, "env"))
		return (ft_env(meta));
	else if (!ft_strcmp(node->command, "export"))
		return (ft_export(node, meta));
	else if (!ft_strcmp(node->command, "unset"))
		return (ft_unset(node, meta));
	return (-1);
}

void	permission_checker(char *path, t_node *node, t_meta *meta)
{
	struct stat	file;

	if (stat(path, &file) == -1)
		exit_error(ERR_FILE, node->command, 127, meta);
	if (S_ISDIR(file.st_mode))
		exit_error(ERR_DIR, node->command, 126, meta);
	if (access(path, X_OK) == -1)
		exit_error(ERR_PERM, NULL, 126, meta);
	exit_error(ERR_CMND, node->command, 127, meta);
}
