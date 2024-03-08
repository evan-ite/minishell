/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/08 10:41:51 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include "executing/executing.h"

int	main(void)
{
	char	*input;
	t_list	*cmnd_list;

	cmnd_list = NULL;
	while(1)
	{
		input = readline("minishell :) ");
		if (!ft_strncmp("exit", input, 4))
		{
			printf("exiting\n");
			free(input);
			break;
		}
		parse(input, &cmnd_list);
		printf("input is: %s\n", input);
		free(input);
	}
	return (0);
}
