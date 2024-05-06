/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:54:04 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/06 12:56:23 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
char c:	character that needs to be checked.

Checks if a character is a special character.
Returns 1 if a special character is found, 0 if none is found.*/
int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '$' || c == '\'' || c == '\"'
		|| c == ' ')
		return (1);
	return (0);
}

/*
Counts how many initial tokens will be required to allocate*/
int	tokencount(char *input)
{
	int	i;
	int	count;
	int	wlen;

	i = -1;
	count = 0;
	while (input[++i])
	{
		if (is_special(input[i]))
			++count;
		else if (ft_isprint(input[i]))
		{
			wlen = 0;
			while ((ft_isprint(input[i + wlen]) == 1)
				&& (!is_special(input[i + wlen])))
				++wlen;
			i += --wlen;
			++count;
		}
		else
			++count;
	}
	return (count);
}
