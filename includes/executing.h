/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:09:02 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/29 13:21:33 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "minishell.h"
# include <sys/fcntl.h>

void	execute(t_list **cmnd_lst, t_meta *meta);

void	open_files(t_node *node, t_list **cmnd_lst);
void	get_path(int i, t_meta *meta, t_node *node);
void	child_process(int i, t_node *node, t_meta *meta);

#endif
