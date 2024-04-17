/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:56:26 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/17 17:29:18 by evan-ite         ###   ########.fr       */
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
		//if ((int)ft_strlen(tokens[i].value) > 1)
		free(tokens[i].value);
		i++;
	}
	if (tokens)
		free(tokens);
}
