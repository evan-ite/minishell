/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/05 17:10:10 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parsing.h"
#include "includes/executing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*cmnd_lst;
	t_meta	meta;

	(void)argc;
	(void)argv;
	cmnd_lst = NULL;
	meta.envp = envp;
	while(1)
	{
		input = readline("\x1b[1;35mminishell :) \x1b[0m");
		if (*input)
		{
			add_history(input);
			if (parse(input, &cmnd_lst))
				execute(&cmnd_lst, &meta);
			free(input);
		}
	}
	rl_clear_history();
	return (0);
}
