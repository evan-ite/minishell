/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:14:57 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/14 10:17:59 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_cd(char *path);
int	ft_pwd(void);
int	ft_export(void);
int	ft_unset(void);
int	ft_echo(char **args);
int	ft_env(void);
int	ft_exit(void);

#endif
