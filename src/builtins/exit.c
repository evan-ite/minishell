/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:38:43 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 18:46:49 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	count_args(t_node *node)
{
	int		i;
	char	*temp;

	if (!node->args)
		return (0);
	i = 0;
	while (node->args[i])
		i++;
	if (i == 3 && (node->args[1][0] == '+' || node->args[1][0] == '-'))
	{
		temp = ft_strjoin(node->args[1], node->args[2]);
		(free(node->args[1]), free(node->args[2]));
		node->args[1] = temp;
		node->args[2] = NULL;
		--i;
	}
	return (i);
}

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && (str[i] != '-' && str[i] != '+'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_node *node, t_meta *meta)
{
	int	args;

	args = count_args(node);
	if (args > 2)
	{
		meta->exit_code = EXIT_FAILURE;
		write(1, "exit\n", 5);
		exit_error(ERR_ARGS, NULL, meta->exit_code, meta);
	}
	else if (args == 2)
	{
		if (!check_numeric(node->args[1]))
		{
			meta->exit_code = 2;
			write(1, "exit\n", 5);
			exit_error(ERR_NUM, node->args[1], meta->exit_code, meta);
		}
		meta->exit_code = ft_atoi(node->args[1]);
	}
	write(1, "exit\n", 5);
	exit_error(NULL, NULL, meta->exit_code, meta);
	return (EXIT_SUCCESS);
}
