/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:27:39 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/16 16:46:31 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	skip_space_redirs(int *i, t_token *tokens)
{
	while (tokens[*i].value && tokens[*i].type == SSPACE)
		(*i)++;
	while (tokens[*i].value && (tokens[*i].type == OUT_APPEND || tokens[*i].type == OUTPUT \
		|| tokens[*i].type == INPUT || tokens[*i].type == HEREDOC))
	{
		(*i)++;
		while (tokens[*i].value && tokens[*i].type == SSPACE)
			(*i)++;
		if (tokens[*i].value && tokens[*i].type == WORD)
			(*i)++;
		while (tokens[*i].value && tokens[*i].type == SSPACE)
			(*i)++;
	}
}

void	get_args(int *i, t_node *node, t_token *tokens)
{
	int	arg_i;
	int	arg_count;
	int	temp_i;

	skip_space_redirs(i, tokens);
	arg_count = 0;
	temp_i = *i;
	while (tokens[temp_i].value && tokens[temp_i].type == WORD)
	{
		if (tokens[temp_i].type == WORD)
			arg_count++;
		temp_i++;
		skip_space_redirs(&temp_i, tokens);
	}
	node->args = (char **)gnl_calloc(arg_count + 1, sizeof(char *));
	arg_i = 0;
	while (tokens[*i].value && tokens[*i].type == WORD)
	{
		node->args[arg_i++] = ft_strdup(tokens[*i].value);
		(*i)++;
		skip_space_redirs(i, tokens);
	}
}
