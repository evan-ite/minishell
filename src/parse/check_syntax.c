/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:58:11 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 13:46:47 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	syntax_quotes(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].type)
	{
		if (tokens[i].type == SQUOTE)
		{
			while (tokens[++i].value && tokens[i].type != SQUOTE)
				;
			if (tokens[i].value == NULL)
				return (EXIT_FAILURE);
		}
		if (tokens[i].type == DQUOTE)
		{
			while (tokens[++i].value && tokens[i].type != DQUOTE)
				;
			if (tokens[i].value == NULL)
				return (EXIT_FAILURE);
		}
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

	i = 0;
	if (syntax_quotes(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (tokens[i].value)
	{
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
