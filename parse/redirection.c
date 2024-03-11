/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:05:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/11 18:13:21 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	get_file(int *i, char **file, t_token *tokens, t_list **cmnd_lst)
{
	(*i)++;
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
	if (tokens[*i].value && tokens[*i].type == WORD)
		*file = ft_strdup(tokens[*i].value);
	else
		exit_error(ERR_SYNT, tokens[*i].value, 1, cmnd_lst);
}

void	parse_redir(t_node *node, t_token *tokens, int i, t_list **cmnd_lst)
{
	// ACCOUNT FOR WEIRD REDIR COMBO'S
	while (tokens[i].value && tokens[i].type != PIPE)
	{
		if (tokens[i].type == INPUT)
			get_file(&i, &node->infile, tokens, cmnd_lst);
		else if (tokens[i].type == OUTPUT || tokens[i].type == OUT_APPEND)
		{
			if (tokens[i].type == OUT_APPEND)
				node->append = 1;
			get_file(&i, &node->outfile, tokens, cmnd_lst);
		}
		else if (tokens[i].type == HEREDOC)
			get_file(&i, &node->heredoc, tokens, cmnd_lst);
		i++;
	}
}
