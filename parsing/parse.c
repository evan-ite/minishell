/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/06 16:54:39 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



void	parse(char *input, t_node **cmnd_lst)
{
	t_token	*tokens;

	tokens = tokenize(input);
	cmnd_lst = NULL;
	printf("print tokens \n");
	for (int i = 0; i < 20; i++)
	{
		printf("type is %u ", tokens[i].type);
		printf("value is '%s'\n", tokens[i].value);
	}
}
