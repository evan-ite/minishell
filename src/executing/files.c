/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:51:26 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 16:25:09 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

int	open_infiles(t_node *node, t_meta *meta)
{
	int	i;

	i = 0;
	while (i < node->n_input)
	{
		if (node->infile[i])
		{
			if (access(node->infile[i], F_OK) != 0)
				exit_error(ERR_FILE, node->infile[i], 1, meta);
			if (access(node->infile[i], R_OK) != 0)
				exit_error(ERR_FPER, node->infile[i], 1, meta);
			node->fd_in[i] = open(node->infile[i], O_RDONLY);
			if (node->fd_in[i] < 0)
				exit_error(ERR_FILE, node->infile[i], 1, meta);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	open_outfiles(t_node *node, t_meta *meta)
{
	int	i;

	i = 0;
	while (i < node->n_output)
	{
		if (node->outfile[i])
		{
			if (access(node->outfile[i], F_OK) == 0)
			{
				if (access(node->outfile[i], W_OK) != 0)
					exit_error(ERR_FPER, node->outfile[i], 1, meta);
			}
			if (node->append[i])
				node->fd_out[i] = open(node->outfile[i], \
								O_CREAT | O_APPEND | O_RDWR, 0644);
			else
				node->fd_out[i] = open(node->outfile[i], \
								O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (node->fd_out[i] < 0)
				exit_error(ERR_FPER, node->outfile[i], 1, meta);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	open_files(t_node *node, t_meta *meta)
{
	open_infiles(node, meta);
	open_outfiles(node, meta);
}
