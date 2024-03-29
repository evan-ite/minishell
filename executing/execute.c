/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:09 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/29 14:57:45 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

void	execute(t_list **cmnd_lst, t_meta *meta)
{
	t_node *node;
	t_list *temp;
	int		i;

	if (!*cmnd_lst)
		exit_error("Empty command list\n", NULL, -1, cmnd_lst);
	meta->n_cmnds = ft_lstsize(*cmnd_lst);
	meta->pid = gnl_calloc(meta->n_cmnds, sizeof(int));
	meta->pipe = gnl_calloc(meta->n_cmnds, sizeof(int));
	if (!meta->pid || !meta->pid)
		exit_error(ERR_MEM, NULL, -1, cmnd_lst);
	i = 0;
	temp = *cmnd_lst;
	while (temp)
	{
		node = temp->content;
		if (node->infile || node->outfile)
			open_files(node, cmnd_lst);
		child_process(i, node, meta);
		i++;
		temp = temp->next;
	}
	i = 0;
	while (i < meta->n_cmnds)
		waitpid(meta->pid[i++], NULL, 0);
	free(meta->pid);
	free_list(cmnd_lst);
}
