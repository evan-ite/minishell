/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:21 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/05 17:19:26 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	clean_node(t_node *node)
{
	if (node->command)
		free(node->command);
	if (node->arguments)
		free_array(node->arguments);
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	if (node)
		free(node);
}

void	free_list(t_list **cmnd_list)
{
	t_list	*temp;

	if (!*cmnd_list || !cmnd_list)
		return ;
	while (*cmnd_list)
	{
		temp = (*cmnd_list)->next;
		clean_node((*cmnd_list)->content);
		free(*cmnd_list);
		*cmnd_list = temp;
	}
	if (*cmnd_list)
		free(*cmnd_list);
}


int	exit_error(char *err_msg, char *src, int err_code, t_list **cmnd_list)
{
	char	*result;

	if (src)
	{
		result = ft_strjoin(src, err_msg);
		if (!result)
		{
			ft_putendl_fd(ERR_MEM, 2);
			exit(-1);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else if (err_msg)
		ft_putendl_fd(err_msg, 2);
	free_list(cmnd_list);
	exit(err_code);
}
