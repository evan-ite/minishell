/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/24 16:13:42 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
int i:				integer to keep track of the index in the token-array
int pipe_from_to:	0 is no pipe, 1 is only pipe from previous, 2 is only pipe
					to next, 3 is both sides.
t_token *tokens:	array of t_token structs, containing token value
					and the corresponding string (char *)
t_meta *meta:		meta struct

Creates a node to add to the back of cmnd_lst, all arguments and redirections
are retrieved and the information is saved in the node. Returns the index in
the token array where the parser should continue. */
static int	parse_command(t_token *tokens, int i, t_meta *meta, int pipe_from_to)
{
	t_node	*node;
	t_list	*new;
	int		start_i;

	start_i = i;
	skip_space_redirs(&i, tokens);
	node = init_node(tokens[i].value);
	get_args(&i, node, tokens);
	parse_redir(node, tokens, start_i, meta);
	while (tokens[i].value && tokens[i].type == SSPACE)
		i++;
	if (pipe_from_to == 1 || pipe_from_to == 3)
		node->pipe_from_prev = 1;
	else if (pipe_from_to == 2 || pipe_from_to == 3)
		node->pipe_to_next = 1;
	new = ft_lstnew(node);
	ft_lstadd_back(meta->cmnd_lst, new);
	return (i);
}

static int	parse_pipes(t_token *tokens, int *i, t_meta *meta, int prev_pipe)
/*
int i:				integer to keep track of the index in the token-array
int prev_pipe:		boolean to indicate the index of the previous pipe
t_token *tokens:	array of t_token structs, containing token value
					and the corresponding string (char *)
t_meta *meta:		meta struct

Handles pipes in the tokenized input, if there's no previous pipe the two
commands left and right of the pipe can be created. Otherwise, the left command
already exists in the cmnd_lst and just the right command needs to be created.
The index in the token array is updated through *i. */
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
	return (EXIT_SUCCESS);
}

static int	check_quotes(t_token *tokens, t_meta *meta)
/*
t_token *tokens:	array of t_token structs, containing token value
					and the corresponding string (char *)
t_meta *meta:		meta struct

Checks if there are quotes in the token-array, if so handle the quotes
with the function parse_quotes. If there's a syntax error, function will return
EXIT_FAILURE (= 1). */
{
	int	i;

	(void)meta;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == SQUOTE)
			parse_quotes(SQUOTE, tokens, &i, meta);
		if (tokens[i].type == DQUOTE)
			parse_quotes(DQUOTE, tokens, &i, meta);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	parse_input(t_token *tokens, t_meta *meta)
/*
t_token *tokens:	array of t_token structs, containing token value
					and the corresponding string (char *)
t_meta *meta:		meta struct

Checks the token-array for environment variables, quotes, and pipes.
If one of those is found they are handled by seperate functions, if none are
found the input is handled as a single command. */
{
	int	i;
	int	prev_pipe;
	int	temp;

	check_quotes(tokens, meta);
	check_env_vars(tokens, meta);
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
	return (EXIT_SUCCESS);
}

/*
char *input:	raw input from the user, string of characters
t_meta *meta:	empty meta struct

Parsing the input by creating a token-array and then interpreting the tokens.
The parsed input is saved in meta->cmnd_lst: a linked list where each node
contains all the information for one command. Returns 0 on succes, 1 on failure.
*/
int	parse(char *input, t_meta *meta)
{
	t_token	*tokens;
	t_list	**lst;
	int		i;

	lst = meta->cmnd_lst;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (EXIT_FAILURE);
	tokens = tokenize(input, meta);
	if (check_syntax(tokens) == 1)
	{
		write(STDOUT_FILENO, ERR_SYNT, 13);
		meta->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (*lst)
	{
		free_list(lst);
		*lst = NULL;
	}
	// for (int i = 0; i < (int)ft_strlen(input); i++)
	// 	printf("token[%i], value '%s', type %i\n", i, tokens[i].value, tokens[i].type);
	parse_input(tokens, meta);
	free_tokens(tokens);
	return (EXIT_SUCCESS);
}
