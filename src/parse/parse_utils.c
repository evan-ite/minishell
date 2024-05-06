/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:27:39 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/06 12:59:08 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	syntax_error(t_meta *meta, t_token *tokens)
{
	write(STDOUT_FILENO, ERR_SYNT, 13);
	meta->exit_code = EXIT_FAILURE;
	free_tokens(tokens);
	return (EXIT_FAILURE);
}

void	skip_space_redirs(int *i, t_token *tokens)
{
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
	while (tokens[*i].value && (tokens[*i].type == OUT_APPEND
			|| tokens[*i].type == OUTPUT || tokens[*i].type == INPUT
			|| tokens[*i].type == HEREDOC))
	{
		(*i)++;
		while (tokens[*i].value && tokens[*i].type == SSPACE)
			(*i)++;
		if (tokens[*i].value && tokens[*i].type == WORD)
			(*i)++;
		while (tokens[*i].value && tokens[*i].type == SSPACE)
			(*i)++;
	}
}

void	get_args(int *i, t_node *node, t_token *tokens)
{
	int	arg_i;
	int	arg_count;
	int	temp_i;

	skip_space_redirs(i, tokens);
	arg_count = 0;
	temp_i = *i;
	while (tokens[temp_i].value && tokens[temp_i].type == WORD)
	{
		if (tokens[temp_i].type == WORD)
			arg_count++;
		temp_i++;
		skip_space_redirs(&temp_i, tokens);
	}
	node->args = (char **)gnl_calloc(arg_count + 1, sizeof(char *));
	arg_i = 0;
	while (tokens[*i].value && tokens[*i].type == WORD)
	{
		node->args[arg_i++] = ft_strdup(tokens[*i].value);
		(*i)++;
		skip_space_redirs(i, tokens);
	}
}

/*
t_token *tokens:	array of t_token structs, containing token value
					and the corresponding string (char *)
t_meta *meta:		meta struct

Checks if there are quotes in the token-array, if so handle the quotes
with the function parse_quotes. If there's a syntax error, function will return
EXIT_FAILURE (= 1). */
int	check_quotes(t_token *tokens, t_meta *meta)
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
