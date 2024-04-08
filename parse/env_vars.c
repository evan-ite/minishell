/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:24:45 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/08 17:35:03 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	handle_var(t_token *tokens, int i)
{

	// print previous exit code
	//if (tokens[i + 1].type == WORD && !ft_strcmp("?", tokens[i + 1].value))

	// else
		// check if env var is in single or dubble quotes
		// if dquotes -> expand
		// if squotes -> don't expand

		// if no quotes -> expand
	if (tokens[i + 1].type == WORD)
		getenv(tokens[i + 1].value);
}

void	check_env_vars(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == DOLLAR)
			handle_var(tokens, i);
		i++;
	}
}
