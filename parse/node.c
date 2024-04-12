/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:24 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/12 12:20:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_node(t_node *node)
{
	int	i;

	printf("------- node --------\n");
	printf("command: %s\n", node->command);
	printf("path: %s\n", node->path);
	i = 0;
	while (node->args[i])
		printf("arguments: %s\n", node->args[i++]);
	printf("infile: %s\n", node->infile);
	printf("fd in: %i\n", node->fd_in);
	printf("outfile: %s\n", node->outfile);
	printf("fd out: %i\n", node->fd_out);
	printf("append: %i\n", node->append);
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
	node->infile = NULL;
	node->fd_in = -1;
	node->outfile = NULL;
	node->fd_out = -1;
	node->append = 0;
	node->heredoc = NULL;
	node->hd_pipe[0] = -1;
	node->hd_pipe[1] = -1;
	node->pipe_to_next = 0;
	node->pipe_from_prev = 0;
	return (node);
}
