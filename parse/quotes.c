/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:06:48 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/10 11:54:09 by evan-ite         ###   ########.fr       */
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
	while (tokens[start + 1].type != end_token && tokens[start + 1].value)
	{
		temp = ft_strjoin(tokens[start].value, tokens[start + 1].value);
		free(tokens[start].value);
		tokens[start].value = ft_strdup(temp);
		free(temp);
		remove_token(tokens, start + 1);
	}
}

void	parse_quotes(token_type quote, t_token *tokens, int *i, t_meta *meta)
{
	int	j;

	j = *i + 1;
	while (tokens[j].type != quote && tokens[j].value)
		j++;
	if (!tokens[j].value)
		exit_error(ERR_SYNT, NULL, 1, meta);
	merge_tokens(*i, tokens, quote);
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].type != quote && tokens[j].value)
		j++;
	remove_token(tokens, j);
	*i = j;
}

// void	parse_dquotes(t_token *tokens, int *i, t_meta *meta)
// {
// 	int	j;

// 	j = *i + 1;
// 	while (tokens[j].type != DQUOTE && tokens[j].value)
// 		j++;
// 	if (!tokens[j].value)
// 		exit_error(ERR_SYNT, NULL, 1, meta);
// 	// HANDLE ENVIRNMENT VARABLES IN DQUOTES
// 	merge_tokens(*i, tokens, DQUOTE);
// 	remove_token(tokens, *i);
// 	j = *i;
// 	while (tokens[j].type != DQUOTE)
// 		j++;
// 	remove_token(tokens, j);
// 	*i = j;
// }
