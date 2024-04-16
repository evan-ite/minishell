/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:21 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/16 13:11:42 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_close(int fd)
{
	close(fd);
	fd = -1;
}

static void	clean_node(t_node *node)
{
	if (node->command)
		free(node->command);
	if (node->path)
		free(node->path);
	if (node->args)
		free_array((void **)node->args, -1);
	if (node->infile)
		free_array((void **)node->infile, node->n_input);
	if (node->outfile)
		free_array((void **)node->outfile, node->n_output);
	if (node->heredoc)
		free_array((void **)node->heredoc, node->n_input);
	if (node->append)
		free(node->append);
	if (node->fd_in)
		free(node->fd_in);
	if (node->fd_out)
		free(node->fd_out);
	if (node->hd_pipe)
		free_array((void **)node->hd_pipe, node->n_input);
	if (node)
		free(node);
}

void	free_list(t_list **cmnd_list)
{
	t_list	*temp;

	if (!cmnd_list || !*cmnd_list)
		return ;
	while (*cmnd_list)
	{
		temp = (*cmnd_list)->next;
		clean_node((*cmnd_list)->content);
		free(*cmnd_list);
		*cmnd_list = temp;
	}
	if (*cmnd_list)
		free(*cmnd_list);
	return ;
}

void	free_meta(t_meta *meta)
{
	if (meta->pid)
		free(meta->pid);
	if (meta->pipe)
		free_array((void **)meta->pipe, -1);
}

int	exit_error(char *err_msg, char *src, int err_code, t_meta *meta)
{
	char	*result;

	if (src)
	{
		result = ft_strjoin(src, err_msg);
		if (!result)
		{
			ft_putendl_fd(ERR_MEM, 2);
			exit(-1);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free_list(meta->cmnd_lst);
	free_meta(meta);
	meta->exit_code = err_code;
	exit(err_code);
}
