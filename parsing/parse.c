/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:24:19 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/08 10:25:46 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	parse_quotes(t_token *tokens, int *i, t_node **cmnd_lst)
// {
// 	// function to handle quotes and increase i
// }

int	parse_command(t_token *tokens, int i, t_list **cmnd_lst)
{
	t_node *node;
	t_list *new;
	int		arg;

	while (tokens[i].type == SSPACE)
		i++;
	node = init_node(tokens[i++].value);
	arg = 1;
	// while (tokens[i].value && tokens[i].type != PIPE)
	// {
	// printf("value %s\n", tokens[i].value);
	while (tokens[i++].type == SSPACE)
	if (tokens[i].type == WORD)
		node->arguments[arg++] = ft_strdup(tokens[i].value);
	// }
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
		// if (tokens[i].type == DQUOTE || tokens[i].type == SQUOTE)
		// 	parse_quotes(tokens, &i, cmnd_lst);
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
}
