/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:09:50 by elisevanite       #+#    #+#             */
/*   Updated: 2024/03/14 13:52:35 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <sys/syslimits.h>

int	ft_pwd(void)
{
	char	*pwd;
	char	buffer[PATH_MAX];

	pwd = getcwd(buffer, sizeof(buffer));
	if (!pwd)
		return (-1);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	free(buffer);
	free(pwd);
	return (EXIT_SUCCESS);
}
