/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:11:09 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/17 16:54:56 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static void	malloc_meta(t_meta *meta)
{
	if (!*(meta->cmnd_lst))
		exit_error("Empty command list\n", NULL, 1, meta);
	meta->n_cmnds = ft_lstsize(*(meta->cmnd_lst));
	meta->pid = gnl_calloc(meta->n_cmnds, sizeof(int));
	if (meta->n_cmnds > 1)
		meta->pipe = gnl_calloc(meta->n_cmnds + 2, sizeof(int *));
	if (!meta->pid || (!meta->pipe && meta->n_cmnds > 1))
		exit_error(ERR_MEM, NULL, 1, meta);
}

static t_list	*parent_builtins(t_meta *meta)
{
	t_list	*temp;
	int		builtin;

	temp = *(meta->cmnd_lst);
	if (ft_lstsize(temp) == 1)
	{
		builtin = firstcheck_builtin(temp->content, meta);
		if ( builtin != -1)
		{
			temp = NULL;
			meta->exit_code = builtin;
		}
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
		// print_node(node);
		child_process(i, node, meta);
		i++;
		temp = temp->next;
	}
	if (i > 0)
	{
		i = 0;
		while (i < meta->n_cmnds)
		{
			waitpid(meta->pid[i++], &status, 0);
			meta->exit_code = WEXITSTATUS(status);
		}
	}
	free_meta(meta);
	free_list(meta->cmnd_lst);
}
