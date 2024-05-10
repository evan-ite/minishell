/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:24 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 16:52:40 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_node(t_node *node)
{
	int	i;

	ft_printf("------- node --------\n");
	ft_printf("command: %s\n", node->command);
	ft_printf("path: %s\n", node->path);
	i = 0;
	while (node->args[i])
		ft_printf("arguments: %s\n", node->args[i++]);
	i = 0;
	while (i < node->n_input)
	{
		ft_printf("infile: %s\n", node->infile[i]);
		ft_printf("fd in: %i\n", node->fd_in[i]);
		ft_printf("heredoc: %s\n", node->heredoc[i++]);
	}
	i = 0;
	while (i < node->n_output)
	{
		ft_printf("outfile: %s\n", node->outfile[i]);
		ft_printf("fd out: %i\n", node->fd_out[i]);
		ft_printf("append: %i\n", node->append[i++]);
	}
	ft_printf("pipe from prev: %i\n", node->pipe_from_prev);
	ft_printf("pipe to next: %i\n", node->pipe_to_next);
}

void	print_list(t_list **head)
{
	t_list	*temp;

	ft_printf("\n------- list ------\n");
	temp = *head;
	while (temp)
	{
		if (temp->content)
			print_node(temp->content);
		else
			ft_printf("(null) ");
		temp = temp->next;
	}
	ft_printf("\n--------------------\n");
}

t_node	*init_node(char *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->args = NULL;
	if (!node)
		return (NULL);
	node->command = ft_strdup(command);
	node->path = NULL;
	node->n_input = 0;
	node->infile = NULL;
	node->outfile = NULL;
	node->heredoc = NULL;
	node->n_output = 0;
	node->append = 0;
	node->fd_in = NULL;
	node->fd_out = NULL;
	node->hd_pipe = NULL;
	node->pipe_to_next = 0;
	node->pipe_from_prev = 0;
	return (node);
}
