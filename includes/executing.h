/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:09:02 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/06 12:41:01 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "minishell.h"
# include "parsing.h"
# include "builtins.h"
# include <sys/ioctl.h>
# include <sys/fcntl.h>
# include <sys/wait.h>

// executing
void	execute(t_meta *meta);
void	child_process(int i, t_node *node, t_meta *meta);

// heredoc
int		check_heredoc(t_node *node, t_meta *meta);
void	sigint_handler_heredoc(int sig);

// files
void	open_files(t_node *node, t_meta *meta);
void	open_outfiles(t_node *node, t_meta *meta);
void	open_infiles(t_node *node, t_meta *meta);

// builtins
int		check_builtin(t_node *node, t_meta *meta);
int		firstcheck_builtin(t_node *node, t_meta *meta);

// utils
void	get_path(t_meta *meta, t_node *node);
void	ft_close(int fd);
char	*remove_nl(char *line);
void	copy_env(char **temp, int *j, t_meta *meta);

#endif
