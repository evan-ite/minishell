/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:27:39 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/08 12:25:38 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

