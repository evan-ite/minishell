/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/03/08 12:28:58 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <stdio.h>

typedef enum {
	WORD,
	SQUOTE,
	DQUOTE,
	INPUT,
	OUTPUT,
	IN_START,
	OUT_APPEND,
	PIPE,
	DOLLAR,
	SSPACE,
}	token_type;

typedef struct s_token {
	token_type	type;
	char		*value;
}	t_token;

// tokenizing and parsing
t_token	*tokenize(char *input);
void	parse(char *input, t_list **cmnd_lst);

// utils
void	remove_token(t_token *tokens, int i);
void	merge_tokens(int start, t_token *tokens, token_type end);
void	print_list(t_list **head);
t_node	*init_node(char *command);
void	print_node(t_node *node);

#endif

