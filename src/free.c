/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:56:26 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/06 12:49:26 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void	free_tokens(t_token	*tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	if (tokens)
		free(tokens);
}

static void	free_files(t_node *node)
{
	if (node->infile)
	{
		free_array((void **)node->infile, node->n_input);
		node->infile = NULL;
	}
	if (node->outfile)
	{
		free_array((void **)node->outfile, node->n_output);
		node->outfile = NULL;
	}
	if (node->heredoc)
	{
		free_array((void **)node->heredoc, node->n_input);
		node->heredoc = NULL;
	}
	if (node->append)
		free(node->append);
	if (node->fd_in)
		free(node->fd_in);
	if (node->fd_out)
		free(node->fd_out);
}

static void	clean_node(t_node *node)
{
	free_files(node);
	if (node->command)
		free(node->command);
	if (node->path)
		free(node->path);
	if (node->args)
	{
		free_array((void **)node->args, -1);
		node->args = NULL;
	}
	if (node->hd_pipe)
	{
		free_array((void **)node->hd_pipe, node->n_input);
		node->hd_pipe = NULL;
	}
	if (node)
		free(node);
}

void	free_list(t_list **cmnd_list)
{
	t_list	*temp;

	if (!cmnd_list || !*cmnd_list)
		return ;
	while (*cmnd_list)
	{
		temp = (*cmnd_list)->next;
		clean_node((*cmnd_list)->content);
		free(*cmnd_list);
		*cmnd_list = temp;
	}
	if (*cmnd_list)
		free(*cmnd_list);
	return ;
}
