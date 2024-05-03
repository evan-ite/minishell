/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:24:00 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/03 16:34:30 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	skip_spaces(int *i, t_token *tokens)
{
	(*i)++;
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
}

int	is_redir(t_token token)
{
	if (token.type == INPUT || token.type == HEREDOC)
		return (1);
	else if (token.type == OUTPUT || token.type == OUT_APPEND)
		return (1);
	else
		return (0);
}

// void	skip_quotes(t_token *tokens, int *i, token_type quote)
// {
// 	int	target;

// 	target = *i;
// 	while (tokens[target].type != quote)
// 		(*i)++;
// }
