/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:09 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 14:39:33 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static void	malloc_meta(t_meta *meta)
{
	if (!*(meta->cmnd_lst))
		exit_error("Empty command list\n", NULL, 1, meta);
	meta->n_cmnds = ft_lstsize(*(meta->cmnd_lst));
	meta->pid = gnl_calloc(meta->n_cmnds, sizeof(int));
	meta->pipe = gnl_calloc(meta->n_cmnds, sizeof(int *));
	if (!meta->pid || !meta->pipe)
		exit_error(ERR_MEM, NULL, 1, meta);
}

static t_list	*parent_builtins(t_meta *meta)
{
	t_list *temp;

	temp = *(meta->cmnd_lst);
	if (ft_lstsize(temp) == 1)
	{
		if (firstcheck_builtin(temp->content, meta) != -1)
			temp = NULL;
	}
	return (temp);
}

void	execute(t_meta *meta)
{
	t_node *node;
	t_list *temp;
	int		i;
	int		status;

	malloc_meta(meta);
	temp = parent_builtins(meta);
	i = 0;
	while (temp)
	{
		node = temp->content;
		child_process(i, node, meta);
		i++;
		temp = temp->next;
	}
	i = 0;
	while (i < meta->n_cmnds)
	{
		waitpid(meta->pid[i++], &status, 0);
		meta->exit_code = WEXITSTATUS(status);
	}
	free(meta->pid);
	free_list(meta->cmnd_lst);
}
