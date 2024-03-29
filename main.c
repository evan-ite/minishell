/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/29 12:56:14 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parsing.h"
#include "includes/executing.h"

int	main(char **envp)
{
	char	*input;
	t_list	*cmnd_lst;
	t_meta	meta;

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
