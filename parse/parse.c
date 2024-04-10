/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/10 12:37:36 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

// Pipe_from_to: 0 is no pipe, 1 is only pipe from prev, 2 is only pipe to next, 3 is both sides.
int	parse_command(t_token *tokens, int i, t_meta *meta, int pipe_from_to)
{
	t_node	*node;
	t_list	*new;
	int		start_i;

	start_i = i;
	skip_space_redirs(&i, tokens);
	node = init_node(tokens[i].value);
	get_args(&i, node, tokens);
	parse_redir(node, tokens, start_i, meta);
	while (tokens[i].type == SSPACE)
		i++;
	if (pipe_from_to == 1 || pipe_from_to == 3)
		node->pipe_from_prev = 1;
	else if (pipe_from_to == 2 || pipe_from_to == 3)
		node->pipe_to_next = 1;
	new = ft_lstnew(node);
	ft_lstadd_back(meta->cmnd_lst, new);
	return (i);
}

void	parse_pipes(t_token *tokens, int *i, t_meta *meta, int prev_pipe)
{
	int		temp_i;
	t_node	*temp_node;

	if (prev_pipe == 0)
		parse_command(tokens, 0, meta, 2);
	else
	{
		temp_node = ft_lstlast(*(meta->cmnd_lst))->content;
		temp_node->pipe_to_next = 1;
	}
	temp_i = parse_command(tokens, *i + 1, meta, 1);
	*i = temp_i;
}

void	parse_input(t_token *tokens, t_meta *meta)
{
	int	i;
	int	prev_pipe;
	int	temp;

	check_env_vars(tokens, meta);
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == SQUOTE)
			parse_quotes(SQUOTE, tokens, &i, meta);
		if (tokens[i].type == DQUOTE)
			parse_quotes(DQUOTE, tokens, &i, meta);
		i++;
	}
	i = 0;
	prev_pipe = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == PIPE)
		{
			temp = i;
			parse_pipes(tokens, &i, meta, prev_pipe);
			prev_pipe = temp;
		}
		else
			i++;
	}
	if (prev_pipe == 0)
		parse_command(tokens, 0, meta, 0);
}

int	parse(char *input, t_meta *meta)
{
	t_token	*tokens;
	t_list **lst;
	int	i;

	lst = meta->cmnd_lst;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (0);
	tokens = tokenize(input);
	if (*lst)
	{
		free_list(lst);
		*lst = NULL;
	}
	parse_input(tokens, meta);
	return (1);
}
