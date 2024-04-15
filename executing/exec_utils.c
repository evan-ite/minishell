/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:29:17 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/15 15:30:43 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static void	open_infiles(t_node *node, t_meta *meta)
{
	int	i;

	i = 0;
	while (i < node->n_input)
	{
		if (node->infile[i])
		{
			printf("checking infile %s \n", node->infile[i]);
			if (access(node->infile[i], F_OK) != 0)
				exit_error(ERR_FILE, node->infile[i], 1, meta);
			if (access(node->infile[i], R_OK) != 0)
				exit_error(ERR_FPER, node->infile[i], 1, meta);
			node->fd_in[i] = open(node->infile[i], O_RDONLY);
			if (node->fd_in[i] < 0)
				exit_error(ERR_FILE, node->infile[i], 1, meta);
		}
		i++;
	}
}

static void	open_outfiles(t_node *node, t_meta *meta)
{
	int	i;

	i = 0;
	while (i < node->n_output)
	{
		if (node->outfile[i])
		{
			printf("checking outfile %s \n", node->outfile[i]);
			if (access(node->outfile[i], F_OK) == 0)
			{
				if (access(node->outfile[i], W_OK) != 0)
					exit_error(ERR_FPER, node->outfile[i], 1, meta);
			}
			if (node->append[i])
				node->fd_out[i] = open(node->outfile[i], \
								O_CREAT | O_APPEND | O_RDWR, 0666);
			else
				node->fd_out[i] = open(node->outfile[i], \
								O_CREAT | O_TRUNC | O_RDWR, 0666);
			if (node->fd_out[i] < 0)
				exit_error(ERR_FILE, node->outfile[i], 1, meta);
		}
		i++;
	}
}

void	open_files(t_node *node, t_meta *meta)
{
	open_infiles(node, meta);
	open_outfiles(node, meta);
}

char	*remove_nl(char *line)
{
	int	len;
	char *temp;

	len = ft_strlen(line);
	temp = NULL;
	if (line[len - 1] == '\n')
		temp = ft_substr(line, 0, len - 1);
	return (temp);
}

int	firstcheck_builtin(t_node *node, t_meta *meta)
{
// EXIT CD UNSET EXPORT need to be in PARENT!!!
	if (!ft_strcmp(node->command, "exit"))
	{
		write(1, "exit\n", 6);
		exit_error(NULL, NULL, 0, meta);
	}
	else if (!ft_strcmp(node->command, "cd"))
		return (ft_cd(node->args));
	else if (!ft_strcmp(node->command, "export"))
		return (ft_export(node, meta));
	else if (!ft_strcmp(node->command, "unset"))
		return (ft_unset(node, meta));
	return (-1);
}

int	check_builtin(t_node *node, t_meta *meta)
{
	if (!ft_strncmp(node->command, "exit", ft_strlen(node->command)))
		exit_error(NULL, NULL, 0, meta);
	else if (!ft_strncmp(node->command, "echo", ft_strlen(node->command)))
		return (ft_echo(node->args));
	else if (!ft_strncmp(node->command, "pwd", ft_strlen(node->command)))
		return (ft_pwd());
	else if (!ft_strncmp(node->command, "cd", ft_strlen(node->command)))
		return (ft_cd(node->args));
	else if (!ft_strncmp(node->command, "env", ft_strlen(node->command)))
		return (ft_env(meta));
	else if (!ft_strcmp(node->command, "export"))
		return (ft_export(node, meta));
	else if (!ft_strcmp(node->command, "unset"))
		return (ft_unset(node, meta));
	return (-1);
}
