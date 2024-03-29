/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:24 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/29 13:08:14 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_node(t_node *node)
{
	int	i;

	printf("------- node --------\n");
	printf("command: %s\n", node->command);
	i = 0;
	while (node->arguments[i])
		printf("arguments: %s\n", node->arguments[i++]);
	printf("infile: %s\n", node->infile);
	printf("outfile: %s\n", node->outfile);
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
	node->arguments = NULL;
	if (!node)
		return (NULL);
	node->command = ft_strdup(command);
	node->infile = NULL;
	node->fd_in = -1;
	node->outfile = NULL;
	node->fd_out = -1;
	node->append = 0;
	node->pipe_to_next = 0;
	node->pipe_from_prev = 0;
	return (node);
}
