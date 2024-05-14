/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:58:11 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/14 15:52:38 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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

static int	syntax_quotes(int *i, t_token *tokens)
{
	t_token_type	quote;

	if (tokens[*i].type != SQUOTE && tokens[*i].type != DQUOTE)
		return (EXIT_SUCCESS);
	quote = tokens[*i].type;
	++*i;
	while (tokens[*i].value && tokens[*i].type != quote)
		++*i;
	if (!tokens[*i].type)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
t_token *tokens:	array of tokens

Function that loops over tokens to check if there are any double pipes,
redirs or unclosed quotes. */
int	check_syntax(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (syntax_quotes(&i, tokens) == 1)
			return (EXIT_FAILURE);
		if (tokens[i].type == PIPE || is_redir(tokens[i]))
		{
			if (check_pipes(i, tokens) == 1)
				return (EXIT_FAILURE);
			if (check_redir(i, tokens) == 1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
