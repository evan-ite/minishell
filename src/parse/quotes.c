/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:06:48 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 18:27:00 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	remove_token(t_token *tokens, int i)
{
	free(tokens[i].value);
	while (tokens[i + 1].value)
	{
		tokens[i] = tokens[i + 1];
		i++;
	}
	tokens[i].value = NULL;
}

void	merge_tokens(int start, t_token *tokens, t_token_type end_token)
{
	char	*temp;

	start++;
	if (tokens[start].type == end_token)
	{
		remove_token(tokens, start);
		return ;
	}
	while (tokens[start + 1].type != end_token && tokens[start + 1].value)
	{
		temp = ft_strjoin(tokens[start].value, tokens[start + 1].value);
		free(tokens[start].value);
		tokens[start].value = ft_strdup(temp);
		free(temp);
		remove_token(tokens, start + 1);
		tokens[start].type = WORD;
	}
}

static void	merge_words(int start, t_token *tokens)
{
	char	*temp;

	if (!tokens || !tokens[start].value || !tokens[start + 1].value)
		return ;
	if (tokens[start].type != WORD)
		start++;
	while (tokens[start + 1].value && tokens[start + 1].type == WORD)
	{
		temp = ft_strjoin(tokens[start].value, tokens[start + 1].value);
		free(tokens[start].value);
		tokens[start].value = ft_strdup(temp);
		free(temp);
		remove_token(tokens, start + 1);
	}
}

int	parse_quotes(t_token_type quote, t_token *tokens, int *i, t_meta *meta)
{
	int	j;
	int	start;

	start = *i;
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].value && tokens[j].type != quote)
	{
		if (tokens[j].type == DOLLAR && quote == DQUOTE)
			handle_var(tokens, j--, meta);
		tokens[j].type = WORD;
		j++;
	}
	if (tokens[j].type == quote)
		remove_token(tokens, j);
	if (tokens[j].value == NULL && j > 0)
		j--;
	if (start > j)
		start = j;
	*i = j;
	if (start > 0 && tokens[start].type == WORD)
		--start;
	merge_words(start, tokens);
	return (EXIT_SUCCESS);
}
