/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:38:41 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/15 15:06:54 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

/* Function to catch the heredoc input until the delimiter
is entered or a signal is catched. */
static void	loop_heredoc(int i, t_node *node)
{
	char	*line;

	while (1 && !g_sig)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-"
				"file\n", STDERR_FILENO);
			break ;
		}
		if (!ft_strncmp(line, node->heredoc[i], ft_strlen(node->heredoc[i])))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, node->hd_pipe[i][1]);
		free(line);
	}
}

/* Returns 1 if the node contains a heredoc and arranges all input and output.
If there's no heredoc the function returns 0. */
int	check_heredoc(t_node *node, t_meta *meta)
{
	int		i;

	if (!node->heredoc)
		return (0);
	signal(SIGINT, sigint_handler_heredoc);
	node->hd_pipe = gnl_calloc(node->n_input, sizeof(int *));
	i = 0;
	while (i < node->n_input)
	{
		if (node->heredoc[i])
		{
			node->hd_pipe[i] = gnl_calloc(2, sizeof(int));
			if (pipe(node->hd_pipe[i]) == -1)
				exit_error(ERR_PIPE, NULL, 1, meta);
			loop_heredoc(i, node);
			ft_close(node->hd_pipe[i][1]);
		}
		i++;
		if (node->heredoc[i] && i < node->n_input)
			ft_close(node->hd_pipe[i - 1][0]);
	}
	return (1);
}
