/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:05:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/10 16:50:58 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
		ft_putendl_fd(ERR_SYNT, STDERR_FILENO);
		meta->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
}

static void	calloc_redirs(t_node *node, t_meta *meta)
{
	if (node->n_input > 0)
	{
		node->infile = gnl_calloc(node->n_input + 1, sizeof(char *));
		node->heredoc = gnl_calloc(node->n_input + 1, sizeof(char *));
		node->fd_in = gnl_calloc(node->n_input + 1, sizeof(int));
		if (!node->infile || !node->heredoc || !node->fd_in)
			exit_error(ERR_MEM, NULL, 1, meta);
	}
	if (node->n_output > 0)
	{
		node->append = gnl_calloc(node->n_output + 1, sizeof(int));
		node->outfile = gnl_calloc(node->n_output + 1, sizeof(char *));
		node->fd_out = gnl_calloc(node->n_output + 1, sizeof(int));
		if (!node->append || !node->outfile || !node->fd_out)
			exit_error(ERR_MEM, NULL, 1, meta);
	}
}

static void	count_redirs(int i, t_node *node, t_token *tokens, t_meta *meta)
{
	while (tokens[i].value)
	{
		if (tokens[i].type == INPUT || tokens[i].type == HEREDOC)
			node->n_input++;
		else if (tokens[i].type == OUTPUT || tokens[i].type == OUT_APPEND)
			node->n_output++;
		else if (tokens[i].type == PIPE)
			break ;
		i++;
	}
	calloc_redirs(node, meta);
}

int	parse_redir(t_node *node, t_token *tokens, int i, t_meta *meta)
{
	int	c_in;
	int	c_out;
	int	syntax_check;

	count_redirs(i, node, tokens, meta);
	c_in = 0;
	c_out = 0;
	while (tokens[i].value && tokens[i].type != PIPE)
	{
		if (tokens[i].type == INPUT)
			syntax_check = get_file(&i, &node->infile[c_in++], tokens, meta);
		else if (tokens[i].type == OUTPUT || tokens[i].type == OUT_APPEND)
		{
			if (tokens[i].type == OUT_APPEND)
				node->append[c_out] = 1;
			syntax_check = get_file(&i, &node->outfile[c_out++], tokens, meta);
		}
		else if (tokens[i].type == HEREDOC)
			syntax_check = get_file(&i, &node->heredoc[c_in++], tokens, meta);
		if (syntax_check == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
