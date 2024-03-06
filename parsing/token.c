/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:34 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/06 12:06:05 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_redirect(int *i, char *input, int count, t_token **tokens)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] && input[*i + 1] == '<')
		{
			(*tokens)[count].type = IN_START;
			(*tokens)[count].value = ft_strjoin(&input[*i], &input[++(*i)]);
			return (0);
		}
		else
			(*tokens)[count].type = INPUT;
		return (1);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] && input[*i + 1] == '>')
		{
			(*tokens)[count].type = OUT_APPEND;
			(*tokens)[count].value = ft_strjoin(&input[*i], &input[++(*i)]);
			return (0);
		}
		else
			(*tokens)[count].type = OUTPUT;
		return (1);
	}
	return (0);
}

int	check_symbol(int *i, char *input, int count, t_token **tokens)
{
	if (input[*i] == '\'')
		(*tokens)[count].type = SQUOTE;
	else if (input[*i] == '\"')
		(*tokens)[count].type = DQUOTE;
	else if (input[*i] == '|')
		(*tokens)[count].type = PIPE;
	else if (input[*i] == '$')
		(*tokens)[count].type = DOLLAR;
	else if (input[*i] == ' ')
		(*tokens)[count].type = SSPACE;
	if (check_redirect(i, input, count, tokens) && (*tokens)[count].type)
	{
		(*tokens)[count].value = &input[*i];
		return (1);
	}
	return (0);
}

int	check_word(int *i, char *input, int count, t_token **tokens)
{
	int	len;

	len = 0;
	while (input[*i + len] && ft_isalnum(input[*i]))
		len++;
	if (len > 0)
	{
		(*tokens)[count].type = WORD;
		(*tokens)[count].value = ft_substr(input, *i, len);
		(*i)+= len;
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
		if (check_symbol(&i, input, count, &tokens))
			count++;
		else if (check_word(&i, input, count, &tokens))
			count++;
		i++;
	}
	printf("print tokens \n");
	for (i = 0; i < 5; i++)
	{
		printf("type is %u\n", tokens[i].type);
		printf("value is %s\n", tokens[i].value);
	}
	return (tokens);
}
