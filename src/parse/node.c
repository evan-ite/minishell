/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:24 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 14:46:25 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_node(t_node *node)
{
	int	i;

	printf("------- node --------\n");
	printf("command: %s\n", node->command);
	printf("path: %s\n", node->path);
	i = 0;
	while (node->args[i])
		printf("arguments: %s\n", node->args[i++]);
	printf("node input files: %i\n", node->n_input);
	i = 0;
	while (i < node->n_input)
	{
		printf("infile: %s\n", node->infile[i]);
		printf("fd in: %i\n", node->fd_in[i]);
		printf("heredoc: %s\n", node->heredoc[i++]);
	}
	printf("node output files: %i\n", node->n_output);
	i = 0;
	while (i < node->n_output)
	{
		printf("outfile: %s\n", node->outfile[i]);
		printf("fd out: %i\n", node->fd_out[i]);
		printf("append: %i\n", node->append[i++]);
	}
	printf("pipe from prev: %i\n", node->pipe_from_prev);
	printf("pipe to next: %i\n", node->pipe_to_next);
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
