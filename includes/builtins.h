/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:14:57 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/16 17:48:08 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "minishell.h"

int	ft_cd(char **args);
int	ft_pwd(void);
int	ft_export(t_node *node, t_meta *meta);
int	ft_unset(t_node *node, t_meta *meta);
int	ft_echo(char **args);
int	ft_env(t_meta *meta);
int	ft_exit(t_node *node, t_meta *meta);

#endif
