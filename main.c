/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/29 14:56:53 by evan-ite         ###   ########.fr       */
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
		execute(&cmnd_lst, &meta);
		printf("input is: %s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
