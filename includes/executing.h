/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:09:02 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/10 14:38:44 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "minishell.h"
# include "parsing.h"
# include "builtins.h"
# include <sys/fcntl.h>
# include <sys/wait.h>

void	execute(t_meta *meta);

void	open_files(t_node *node, t_meta *meta);
void	get_path(int i, t_meta *meta, t_node *node);
void	child_process(int i, t_node *node, t_meta *meta);
int		check_builtin(t_node *node, t_meta *meta);
int		firstcheck_builtin(t_node *node, t_meta *meta);
void	ft_close(int fd);
void	copy_env(char **temp, int *j, t_meta *meta);

#endif
