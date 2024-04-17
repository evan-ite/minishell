/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:05:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/17 11:32:27 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	get_file(int *i, char **file, t_token *tokens, t_meta *meta)
{
	(*i)++;
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
	if (tokens[*i].value && tokens[*i].type == WORD)
	{
		*file = ft_strdup(tokens[*i].value);
		if (!*file)
			exit_error(ERR_MEM, NULL, 1, meta);
		return (EXIT_SUCCESS);
	}
	else
	{
		write(STDOUT_FILENO, ERR_SYNT, 13);
		meta->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
}

static void	count_redirs(t_node *node, t_token *tokens, t_meta *meta)
{
	int	i;

	i = 0;
	node->n_input = 0;
	node->n_output = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == INPUT || tokens[i].type == HEREDOC)
			node->n_input++;
		else if (tokens[i].type == OUTPUT || tokens[i].type == OUT_APPEND)
			node->n_output++;
		i++;
	}
	if (node->n_input > 0)
	{
		node->infile = gnl_calloc(node->n_input, sizeof(char *));
		node->heredoc = gnl_calloc(node->n_input, sizeof(char *));
		node->fd_in = gnl_calloc(node->n_input, sizeof(int));
		if (!node->infile || !node->heredoc || !node->fd_in)
			exit_error(ERR_MEM, NULL, 1, meta);
	}
	if (node->n_output > 0)
	{
		node->append = gnl_calloc(node->n_output, sizeof(int));
		node->outfile = gnl_calloc(node->n_output, sizeof(char *));
		node->fd_out = gnl_calloc(node->n_output, sizeof(int));
		if (!node->append || !node->outfile || !node->fd_out)
			exit_error(ERR_MEM, NULL, 1, meta);
	}
}

int	parse_redir(t_node *node, t_token *tokens, int i, t_meta *meta)
{
	int	in_count;
	int	out_count;
	int	syntax_check;

	count_redirs(node, tokens, meta);
	in_count = 0;
	out_count = 0;
	while (tokens[i].value && tokens[i].type != PIPE)
	{
		if (tokens[i].type == INPUT)
			syntax_check = get_file(&i, &node->infile[in_count++], tokens, meta);
		else if (tokens[i].type == OUTPUT || tokens[i].type == OUT_APPEND)
		{
			if (tokens[i].type == OUT_APPEND)
				node->append[out_count] = 1;
			syntax_check = get_file(&i, &node->outfile[out_count++], tokens, meta);
		}
		else if (tokens[i].type == HEREDOC)
			syntax_check = get_file(&i, &node->heredoc[in_count++], tokens, meta);
		if (syntax_check == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
