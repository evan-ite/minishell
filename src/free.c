/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:56:26 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/01 18:42:37 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void	free_tokens(t_token	*tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	if (tokens)
		free(tokens);
}
