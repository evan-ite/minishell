/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:21 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/15 14:53:17 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_close(int fd)
{
	close(fd);
	fd = -1;
}

static void	clean_node(t_node *node)
{
	if (node->command)
		free(node->command);
	if (node->args)
		free_array(node->args);
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	if (node->heredoc)
		free(node->heredoc);
	if (node)
		free(node);
}

void	free_list(t_list **cmnd_list)
{
	t_list	*temp;

	if (!cmnd_list || !*cmnd_list)
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
	return ;
}


int	exit_error(char *err_msg, char *src, int err_code, t_meta *meta)
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
	free_list(meta->cmnd_lst);
	// free meta struct
	meta->exit_code = err_code;
	exit(err_code);
}
