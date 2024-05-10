/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:29:17 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/10 20:30:28 by tsurma           ###   ########.fr       */
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
	if (!ft_strncmp(node->command, "exit", ft_strlen(node->command)))
		ft_exit(node, meta);
	else if (!ft_strncmp(node->command, "cd", ft_strlen(node->command)))
		return (ft_cd(node->args, meta));
	else if (!ft_strncmp(node->command, "export", ft_strlen(node->command)))
		return (ft_export(node, meta));
	else if (!ft_strncmp(node->command, "unset", ft_strlen(node->command)))
		return (ft_unset(node, meta));
	return (-1);
}

int	check_builtin(t_node *node, t_meta *meta)
{
	if (!node->command)
		return (EXIT_FAILURE);
	if (!ft_strncmp(node->command, "exit", ft_strlen(node->command)))
		ft_exit(node, meta);
	else if (!ft_strncmp(node->command, "echo", ft_strlen(node->command)))
		return (ft_echo(node->args));
	else if (!ft_strncmp(node->command, "pwd", ft_strlen(node->command)))
		return (ft_pwd());
	else if (!ft_strncmp(node->command, "cd", ft_strlen(node->command)))
		return (ft_cd(node->args, meta));
	else if (!ft_strncmp(node->command, "env", ft_strlen(node->command)))
		return (ft_env(meta));
	else if (!ft_strncmp(node->command, "export", ft_strlen(node->command)))
		return (ft_export(node, meta));
	else if (!ft_strncmp(node->command, "unset", ft_strlen(node->command)))
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
