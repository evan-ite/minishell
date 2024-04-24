/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:58:11 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/24 20:28:23 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	is_redir(t_token token)
{
	if (token.type == INPUT || token.type == HEREDOC)
		return (1);
	else if (token.type == OUTPUT || token.type == OUT_APPEND)
		return (1);
	else
		return (0);
}

static int	quote_closed(int start, t_token *tokens, token_type quote)
{
	int	i;

	i = start + 1;
	while (tokens[i].value && tokens[i].type != quote)
		i++;
	if (!tokens[i].value)
		return (0);
	else
		return (1);
}

static void	skip_spaces(int *i, t_token *tokens)
{
	(*i)++;
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
}

static int	find_quotes(int *squote, int *dquote, int i, t_token *tokens)
{
	if (tokens[i].type == SQUOTE)
	{
		(*squote)++;
		if (*squote % 2 && quote_closed(i, tokens, tokens[i].type) == 0)
			return (EXIT_FAILURE);
	}
	else if (tokens[i].type == DQUOTE)
	{
		(*dquote)++;
		if (*dquote % 2 && quote_closed(i, tokens, tokens[i].type) == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_pipes(int i, t_token *tokens)
{
	if (tokens[i].type == PIPE)
	{
		if (i == 0 || is_redir(tokens[i - 1]))
			return (EXIT_FAILURE);
		skip_spaces(&i, tokens);
		if (!tokens[i].value)
			return (EXIT_FAILURE);
		else if (tokens[i].type == PIPE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_redir(int i, t_token *tokens)
{
	if (is_redir(tokens[i]))
	{
		skip_spaces(&i, tokens);
		if (!tokens[i].value)
			return (EXIT_FAILURE);
		else if (is_redir(tokens[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
t_token *tokens:	array of tokens

Function that loops over tokens to check if there are any double pipes,
redirs or unclosed quotes. */
int	check_syntax(t_token *tokens)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (tokens[i].value)
	{
		if (find_quotes(&squote, &dquote, i, tokens) == 1)
			return (EXIT_FAILURE);
		if (check_pipes(i, tokens) == 1)
			return (EXIT_FAILURE);
		if (check_redir(i, tokens) == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
