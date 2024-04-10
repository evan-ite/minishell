/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:05:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/10 11:47:45 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	get_file(int *i, char **file, t_token *tokens, t_meta *meta)
{
	(*i)++;
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
	if (tokens[*i].value && tokens[*i].type == WORD)
	{
		*file = ft_strdup(tokens[*i].value);
		if (!*file)
			exit_error(ERR_MEM, NULL, 1, meta);
	}
	else
		exit_error(": Error parsing file\n", tokens[*i].value, 1, meta);
}

void	parse_redir(t_node *node, t_token *tokens, int i, t_meta *meta)
{
	// ACCOUNT FOR WEIRD REDIR COMBO'S
	while (tokens[i].value && tokens[i].type != PIPE)
	{
		if (tokens[i].type == INPUT)
			get_file(&i, &node->infile, tokens, meta);
		else if (tokens[i].type == OUTPUT || tokens[i].type == OUT_APPEND)
		{
			if (tokens[i].type == OUT_APPEND)
				node->append = 1;
			get_file(&i, &node->outfile, tokens, meta);
		}
		else if (tokens[i].type == HEREDOC)
			get_file(&i, &node->heredoc, tokens, meta);
		i++;
	}
}
