/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:29:17 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 16:50:18 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

void	open_files(t_node *node, t_meta *meta)
{
	if (node->infile)
	{
		if (access(node->infile, F_OK) != 0)
			exit_error(ERR_FILE, node->infile, 1, meta);
		if (access(node->infile, R_OK) != 0)
			exit_error(ERR_FPER, node->infile, 1, meta);
		node->fd_in = open(node->infile, O_RDONLY);
		if (node->fd_in < 0)
			exit_error(ERR_FILE, node->infile, 1, meta);
	}
	if (node->outfile)
	{
		if (access(node->outfile, F_OK) == 0)
		{
			if (access(node->outfile, W_OK) != 0)
				exit_error(ERR_FPER, node->outfile, 1, meta);
		}
		if (node->append)
			node->fd_out = open(node->outfile, \
							O_CREAT | O_APPEND | O_RDWR, 0666);
		else
			node->fd_out = open(node->outfile, \
							O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (node->fd_out < 0)
			exit_error(ERR_FILE, node->outfile, 1, meta);
	}
}

void	ft_close(int fd)
{
	close(fd);
	fd = -1;
}

int	firstcheck_builtin(t_node *node, t_meta *meta)
{
// EXIT CD UNSET EXPORT need to be in PARENT!!!
	if (!ft_strcmp(node->command, "exit"))
	{
		write(1, "exit\n", 6);
		exit_error(NULL, NULL, 0, meta);
	}
	else if (!ft_strcmp(node->command, "cd"))
		return (ft_cd(node->args));
	else if (!ft_strcmp(node->command, "export"))
		return (ft_export(node, meta));
	else if (!ft_strcmp(node->command, "unset"))
		return (ft_unset(node, meta));
	return (-1);
}

int	check_builtin(t_node *node, t_meta *meta)
{
	if (!ft_strncmp(node->command, "exit", ft_strlen(node->command)))
		exit_error(NULL, NULL, 0, meta);
	else if (!ft_strncmp(node->command, "echo", ft_strlen(node->command)))
		return (ft_echo(node->args));
	else if (!ft_strncmp(node->command, "pwd", ft_strlen(node->command)))
		return (ft_pwd());
	else if (!ft_strncmp(node->command, "cd", ft_strlen(node->command)))
		return (ft_cd(node->args));
	else if (!ft_strncmp(node->command, "env", ft_strlen(node->command)))
		return (ft_env(meta));
	else if (!ft_strcmp(node->command, "export"))
		return (ft_export(node, meta));
	else if (!ft_strcmp(node->command, "unset"))
		return (ft_unset(node, meta));
	return (-1);
}
