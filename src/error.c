/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:21 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/06 12:48:03 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close(int fd)
{
	close(fd);
	fd = -1;
}

void	free_meta(t_meta *meta)
{
	if (meta->pid)
	{
		free(meta->pid);
		meta->pid = NULL;
	}
	if (meta->pipe)
	{
		free_array((void **)meta->pipe, meta->n_cmnds + 1);
		meta->pipe = NULL;
	}
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
	free_meta(meta);
	meta->exit_code = err_code;
	exit(err_code);
}
