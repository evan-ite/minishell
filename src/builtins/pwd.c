/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:50 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/17 17:34:21 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include <linux/limits.h>

int	ft_pwd(void)
{
	char	*pwd;
	char	buffer[PATH_MAX];

	pwd = getcwd(buffer, sizeof(buffer));
	if (!pwd)
	{
		ft_putstr_fd("Error pwd\n", STDERR_FILENO);
		return (-1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
