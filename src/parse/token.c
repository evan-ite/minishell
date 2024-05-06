/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:34 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/06 12:56:48 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
int *i:				integer pointing to the index in the input string.
char *input:		raw input from the user, string of characters
int count:			index in the token-array
t_token *tokens:	array of tokens

Checks for redirections and creates a token if one is found.
Returns 1 if > or < is found, returns 2 if >> or << is found,
and returns 0 nothing was found.*/
int	check_redirect(int *i, char *input, int count, t_token *tokens)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] && input[*i + 1] == '<')
		{
			(tokens)[count].type = HEREDOC;
			(tokens)[count].value = ft_substr(input, (*i)++, 2);
			return (2);
		}
		else
			(tokens)[count].type = INPUT;
		return (1);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] && input[*i + 1] == '>')
		{
			(tokens)[count].type = OUT_APPEND;
			(tokens)[count].value = ft_substr(input, (*i)++, 2);
			return (2);
		}
		else
			(tokens)[count].type = OUTPUT;
		return (1);
	}
	return (0);
}

/*
int *i:				integer pointing to the index in the input string.
char *input:		raw input from the user, string of characters
int count:			index in the token-array
t_token *tokens:	array of tokens

Checks if a character is a special character, if a special character is found
a new token is created. Returns 1 on succes, 0 on failure. */
int	check_symbol(int *i, char *input, int count, t_token *tokens)
{
	int	found_redir;

	if (input[*i] == '\'')
		(tokens)[count].type = SQUOTE;
	else if (input[*i] == '\"')
		(tokens)[count].type = DQUOTE;
	else if (input[*i] == '|')
		(tokens)[count].type = PIPE;
	else if (input[*i] == '$')
		(tokens)[count].type = DOLLAR;
	else if (ft_isspace(input[*i]))
		(tokens)[count].type = SSPACE;
	found_redir = check_redirect(i, input, count, tokens);
	if (found_redir == 1 || ((tokens)[count].type && \
		(tokens)[count].type != OUT_APPEND && (tokens)[count].type != HEREDOC))
	{
		(tokens)[count].value = ft_substr(input, *i, 1);
		return (1);
	}
	else if (found_redir == 2)
		return (1);
	return (0);
}

/*
int *i:				integer pointing to the index in the input string.
char *input:		raw input from the user, string of characters
int count:			index in the token-array
t_token *tokens:	array of tokens

Checks if a combination of characters is a word, a word cannot contain
spaces or special characters. If a word is found, a new WORD token is created.
Returns 1 on succes, 0 on failure. */
int	check_word(int *i, char *input, int count, t_token *tokens)
{
	int	len;

	len = 0;
	while (input[*i + len] && ft_isprint(input[*i + len])
		&& !is_special(input[*i + len]))
		len++;
	if (len > 0)
	{
		(tokens)[count].type = WORD;
		(tokens)[count].value = ft_substr(input, *i, len);
		(*i) += len - 1;
		return (1);
	}
	return (0);
}

/*
char *input:	raw input from the user, string of characters

Create an array of tokens, loop over raw user input and assign
tokens to characters. Returns the array of tokens. */
t_token	*tokenize(char *input, t_meta *meta)
{
	t_token	*tokens;
	int		i;
	int		count;

	tokens = gnl_calloc(tokencount(input) + 1, sizeof(t_token));
	if (!tokens)
		exit_error(ERR_MEM, NULL, 1, meta);
	i = 0;
	count = 0;
	while (input[i])
	{
		if (check_symbol(&i, input, count, tokens))
			count++;
		else if (check_word(&i, input, count, tokens))
			count++;
		i++;
	}
	tokens[count].type = 0;
	tokens[count].value = NULL;
	i = -1;
	return (tokens);
}
