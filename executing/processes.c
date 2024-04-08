/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:13 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/08 15:51:59 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static int	execute_cmnd(int i, t_node *node, t_meta *meta)
{
	int	builtin;
	// IS PIPE OR REDIRECTION MORE IMPORTANT IN IF-ELSE?
	if (node->infile)
		dup2(node->fd_in, STDIN_FILENO);
	else if (node->pipe_from_prev)
	{
		dup2(meta->pipe[i][0], STDIN_FILENO);
		ft_close(meta->pipe[i][1]);
	}
	if (node->outfile)
		dup2(node->fd_out, STDOUT_FILENO);
	else if (node->pipe_to_next)
	{
		dup2(meta->pipe[i + 1][1], STDOUT_FILENO);
		ft_close(meta->pipe[i + 1][0]);
	}
	builtin = check_builtin(node, meta);
	if (builtin == -1)
	{
		get_path(i, meta, node);
		if (execve(node->path, node->args, meta->envp) == -1)
			exit_error(ERR_EXC, node->command, 2, meta->cmnd_lst);
	}
	else
		exit(builtin);
	return (EXIT_SUCCESS);
}

void	child_process(int i, t_node *node, t_meta *meta)
{
	if (node->pipe_to_next)
	{
		meta->pipe[i + 1] = gnl_calloc(2, sizeof(int));
		if (pipe(meta->pipe[i + 1]) == -1)
			exit_error(ERR_PIPE, NULL, 3, meta->cmnd_lst);
	}
	meta->pid[i] = fork();
	if (meta->pid[i] < 0)
		exit_error(ERR_CHILD, NULL, 4, meta->cmnd_lst);
	else if (meta->pid[i] == 0)
	{
		if (execute_cmnd(i, node, meta) != 0)
			exit_error(ERR_EXC, node->command, 2, meta->cmnd_lst);
	}
	else
	{
		if (i > 0)
		{
			ft_close(meta->pipe[i][0]);
			ft_close(meta->pipe[i][1]);
		}
	}
}
