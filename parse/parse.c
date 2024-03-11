/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/11 18:11:47 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Pipe_from_to: 0 is no pipe, 1 is only pipe from prev, 2 is only pipe to next, 3 is both sides.
int	parse_command(t_token *tokens, int i, t_list **cmnd_lst, int pipe_from_to)
{
	t_node	*node;
	t_list	*new;
	int		start_i;

	start_i = i;
	skip_space_redirs(&i, tokens);
	node = init_node(tokens[i].value);
	get_args(&i, node, tokens);
	parse_redir(node, tokens, start_i, cmnd_lst);
	while (tokens[i].type == SSPACE)
		i++;
	if (pipe_from_to == 1 || pipe_from_to == 3)
		node->pipe_from_prev = 1;
	else if (pipe_from_to == 2 || pipe_from_to == 3)
		node->pipe_to_next = 1;
	new = ft_lstnew(node);
	ft_lstadd_back(cmnd_lst, new);
	return (i);
}

void	parse_pipes(t_token *tokens, int *i, t_list **cmnd_lst, int prev_pipe)
{
	int		temp_i;
	t_node	*temp_node;

	if (prev_pipe == 0)
		parse_command(tokens, 0, cmnd_lst, 2);
	else
	{
		temp_node = ft_lstlast(*cmnd_lst)->content;
		temp_node->pipe_to_next = 1;
	}
	temp_i = parse_command(tokens, *i + 1, cmnd_lst, 1);
	*i = temp_i;
}

void	parse_input(t_token *tokens, t_list **cmnd_lst)
{
	int	i;
	int	prev_pipe;
	int	temp;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == SQUOTE)
			parse_squotes(tokens, &i, cmnd_lst);
		if (tokens[i].type == DQUOTE)
			parse_dquotes(tokens, &i, cmnd_lst);
		i++;
	}
	i = 0;
	prev_pipe = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == PIPE)
		{
			temp = i;
			parse_pipes(tokens, &i, cmnd_lst, prev_pipe);
			prev_pipe = temp;
		}
		else
			i++;
	}
	if (prev_pipe == 0)
		parse_command(tokens, 0, cmnd_lst, 0);
}

void	parse(char *input, t_list **cmnd_lst)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (*cmnd_lst)
	{
		free_list(cmnd_lst);
		*cmnd_lst = NULL;
	}
	parse_input(tokens, cmnd_lst);
	// int i = 0;
	// while (tokens[i].value)
	// {
	// 	printf("tokentype %i value %s\n", tokens[i].type, tokens[i].value);
	// 	i++;
	// }
}
