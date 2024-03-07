/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:24 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/07 16:49:13 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_node(t_node *node)
{
	int	i;

	printf("command: %s\n", node->command);
	i = 0;
	while (node->arguments[i])
		printf("arguments: %s\n", node->arguments[i++]);
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
	node->arguments = (char **)gnl_calloc(3, sizeof(char *));
	if (!node)
		return (NULL);
	node->command = ft_strdup(command);
	node->arguments[0] = ft_strdup(command);
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->pipe_to_next = 0;
	node->pipe_from_prev = 0;
	return (node);
}
