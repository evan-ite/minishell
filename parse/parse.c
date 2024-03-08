/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/08 12:54:49 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_squotes(t_token *tokens, int *i, t_list **cmnd_lst)
{
	int	j;

	j = *i + 1;
	while (tokens[j].type != SQUOTE && tokens[j].value)
		j++;
	if (!tokens[j].value)
		exit_error(ERR_SYNT, NULL, 1, cmnd_lst);
	merge_tokens(*i, tokens, SQUOTE);
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].type != SQUOTE && tokens[j].value)
		j++;
	remove_token(tokens, j);
	*i = j;
}

void	parse_dquotes(t_token *tokens, int *i, t_list **cmnd_lst)
{
	int	j;

	j = *i + 1;
	while (tokens[j].type != DQUOTE && tokens[j].value)
		j++;
	if (!tokens[j].value)
		exit_error(ERR_SYNT, NULL, 1, cmnd_lst);
	// j = *i;
	// while (tokens[j].type != DOLLAR && tokens[j].value)
	// 	j++;
	// if (tokens[j].type == DOLLAR)
	// {
	// 	merge_tokens(*i, tokens, DOLLAR);
	// 	while (tokens[j].type != SSPACE && tokens[j].type != DQUOTE && tokens[j].value)
	// 		j++;
	// 	merge_tokens(j, tokens, DQUOTE);
	// }
	// else
		merge_tokens(*i, tokens, DQUOTE);
	remove_token(tokens, *i);
	j = *i;
	while (tokens[j].type != DQUOTE)
		j++;
	remove_token(tokens, j);
	*i = j;
}

int	parse_command(t_token *tokens, int i, t_list **cmnd_lst)
{
	t_node *node;
	t_list *new;
	int		arg;

	while (tokens[i].type == SSPACE)
		i++;
	node = init_node(tokens[i++].value);
	arg = 1;
	while (tokens[i++].type == SSPACE)
	if (tokens[i].type == WORD)
		node->arguments[arg++] = ft_strdup(tokens[i].value);
	new = ft_lstnew(node);
	ft_lstadd_back(cmnd_lst, new);
	return (++i);
}

void	parse_pipes(t_token *tokens, int *i, t_list **cmnd_lst)
{
	int	temp;
	
	parse_command(tokens, 0, cmnd_lst);
	temp = parse_command(tokens, *i + 1, cmnd_lst);
	*i = temp;
	print_list(cmnd_lst);
}

void	parse_input(t_token *tokens, t_list **cmnd_lst)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == SQUOTE)
			parse_squotes(tokens, &i, cmnd_lst);
		if (tokens[i].type == DQUOTE)
			parse_dquotes(tokens, &i, cmnd_lst);
		if (tokens[i].type == PIPE)
			parse_pipes(tokens, &i, cmnd_lst);
		i++;
	}
}

void	parse(char *input, t_list **cmnd_lst)
{
	t_token	*tokens;

	tokens = tokenize(input);
	printf("print tokens \n");
	for (int i = 0; i < 6; i++)
	{
		printf("type is %u ", tokens[i].type);
		printf("value is '%s'\n", tokens[i].value);
	}
	parse_input(tokens, cmnd_lst);
	printf("print tokens final \n");
	for (int i = 0; i < 11; i++)
	{
		printf("type is %u ", tokens[i].type);
		printf("value is '%s'\n", tokens[i].value);
	}
}
