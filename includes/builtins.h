/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:14:57 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/05 18:20:19 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

int	ft_cd(char **args);
int	ft_pwd(void);
int	ft_export(void);
int	ft_unset(void);
int	ft_echo(char **args);
int	ft_env(void);

#endif
