/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:29:17 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/29 12:57:33 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

void	open_files(t_node *node, t_list **cmnd_lst)
{
	if (node->infile)
	{
		if (access(node->infile, F_OK) != 0)
			exit_error(ERR_FILE, node->infile, 2, cmnd_lst);
		if (access(node->infile, R_OK) != 0)
			exit_error(ERR_FPER, node->infile, 2, cmnd_lst);
		node->fd_in = open(node->infile, O_RDONLY);
		if (node->fd_in < 0)
			exit_error(ERR_FILE, node->infile, 2, cmnd_lst);
	}
	if (node->outfile)
	{
		if (access(node->outfile, F_OK) == 0)
		{
			if (access(node->outfile, W_OK) != 0)
				exit_error(ERR_FPER, node->outfile, 2, cmnd_lst);
		}
		node->fd_out = open(node->outfile, \
							O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (node->fd_out < 0)
			exit_error(ERR_FILE, node->outfile, 2, cmnd_lst);
	}
}

