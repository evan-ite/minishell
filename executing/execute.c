/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:09 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 12:42:03 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

void	execute(t_list **cmnd_lst, t_meta *meta)
{
	t_node *node;
	t_list *temp;
	int		i;

	if (!*cmnd_lst)
		exit_error("Empty command list\n", NULL, 1, meta);
	meta->n_cmnds = ft_lstsize(*cmnd_lst);
	meta->pid = gnl_calloc(meta->n_cmnds, sizeof(int));
	meta->pipe = gnl_calloc(meta->n_cmnds, sizeof(int *));
	if (!meta->pid || !meta->pipe)
		exit_error(ERR_MEM, NULL, 1, meta);
	i = 0;
	temp = *cmnd_lst;
	if (ft_lstsize(*cmnd_lst) == 1)
	{
		if (check_parent_builtins(temp->content, meta) != -1)
			temp = NULL;
	}
	while (temp)
	{
		node = temp->content;
		child_process(i, node, meta);
		i++;
		temp = temp->next;
	}
	i = 0;
	while (i < meta->n_cmnds)
		waitpid(meta->pid[i++], &(meta->exit_code), 0);
	free(meta->pid);
	free_list(cmnd_lst);
}
