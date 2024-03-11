/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/11 12:47:34 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_squotes(t_token *tokens, int *i, t_list **cmnd_lst)
{
	int	j;

	j = *i + 1;
	while (tokens[j].type != SQUOTE && tokens[j].value)
		j++;
	if (!tokens[j].value)
		exit_error(ERR_SYNT, NULL, 1, cmnd_lst);
	merge_tokens(*i, tokens, SQUOTE);
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].type != SQUOTE && tokens[j].value)
		j++;
	remove_token(tokens, j);
	*i = j;
}

void	parse_dquotes(t_token *tokens, int *i, t_list **cmnd_lst)
{
	int	j;

	j = *i + 1;
	while (tokens[j].type != DQUOTE && tokens[j].value)
		j++;
	if (!tokens[j].value)
		exit_error(ERR_SYNT, NULL, 1, cmnd_lst);
	// HANDLE ENVIRNMENT VARABLES IN DQUOTES
	merge_tokens(*i, tokens, DQUOTE);
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].type != DQUOTE)
		j++;
	remove_token(tokens, j);
	*i = j;
}

void	parse_redir(t_node *node, t_token *tokens, int i)
{
	char	*infile;
	char	*outfile;

	while (tokens[i].value && tokens[i].type != PIPE)
	{
		if (tokens[i].type == INPUT)
		{

		}
		else if (tokens[i].type == OUTPUT)
		{

		}
		else if (tokens[i].type == OUT_APPEND)
		{

		}
		else if (tokens[i].type == IN_START)
		{
			
		}
		i++;
	}
}

// Pipe_from_to: 0 is no pipe, 1 is only pipe from prev, 2 is only pipe to next, 3 is both sides.
int	parse_command(t_token *tokens, int i, t_list **cmnd_lst, int pipe_from_to)
{
	t_node	*node;
	t_list	*new;
	int		start_i;

	start_i = i;
	while (tokens[i].type == SSPACE)
		i++;
	node = init_node(tokens[i++].value);
	parse_redir(node, tokens, start_i);
	while (tokens[i].type == SSPACE)
		i++;
	// ALSO NEED TO CATCH SEVERAL ARGS
	if (tokens[i].value && tokens[i].type == WORD)
		node->arguments[1] = ft_strdup(tokens[i].value);
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
	print_list(cmnd_lst);
}
