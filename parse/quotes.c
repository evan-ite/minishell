/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:06:48 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/16 16:54:36 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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

void	merge_tokens(int start, t_token *tokens, token_type end_token)
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
	}
}

static void	merge_words(int start, t_token *tokens)
{
	char	*temp;

	start--;
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

int	parse_quotes(token_type quote, t_token *tokens, int *i, t_meta *meta)
{
	int	j;
	int	start;

	start = *i;
	j = *i + 1;
	while (tokens[j].type != quote && tokens[j].value)
		j++;
	if (!tokens[j].value)
	{
		write(STDOUT_FILENO, ERR_SYNT, 13);
		meta->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	merge_tokens(*i, tokens, quote);
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].type != quote && tokens[j].value)
		j++;
	remove_token(tokens, j);
	*i = j;
	merge_words(start, tokens);
	return (EXIT_SUCCESS);
}
