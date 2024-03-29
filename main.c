/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/13 16:30:00 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse/parsing.h"
#include "executing/executing.h"

int	main(void)
{
	char	*input;
	t_list	*cmnd_lst;

	cmnd_lst = NULL;
	while(1)
	{
		input = readline("minishell :) ");
		add_history(input);
		if (!ft_strncmp("exit", input, 4))
		{
			printf("exiting\n");
			free(input);
			break;
		}
		parse(input, &cmnd_lst);
		print_list(&cmnd_lst);
		printf("input is: %s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
