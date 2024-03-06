/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:34 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/06 16:55:42 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '$')
		return (1);
	else if (c == '\'' || c == '\"' || c == ' ')
		return (1);
	return (0);
}

int	check_redirect(int *i, char *input, int count, t_token *tokens)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] && input[*i + 1] == '<')
		{
			(tokens)[count].type = IN_START;
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
	else if (input[*i] == ' ')
		(tokens)[count].type = SSPACE;
	found_redir = check_redirect(i, input, count, tokens);
	if (found_redir == 1 || ((tokens)[count].type && \
		(tokens)[count].type != OUT_APPEND && (tokens)[count].type != IN_START))
	{
		(tokens)[count].value = ft_substr(input, *i, 1);
		return (1);
	}
	else if (found_redir == 2)
		return (1);
	return (0);
}

int	check_word(int *i, char *input, int count, t_token *tokens)
{
	int	len;

	len = 0;
	while (input[*i + len] && ft_isprint(input[*i + len]))
	{
		if (is_special(input[*i + len]))
			break ;
		len++;
	}
	if (len > 0)
	{
		(tokens)[count].type = WORD;
		(tokens)[count].value = ft_substr(input, *i, len);
		(*i) += len - 1;
		return (1);
	}
	return (0);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	int		count;

	tokens = gnl_calloc(ft_strlen(input), sizeof(t_token));
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
	return (tokens);
}
