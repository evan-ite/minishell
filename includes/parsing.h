/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/04/17 15:51:50 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdio.h>

typedef enum {
	WORD,
	SQUOTE,
	DQUOTE,
	INPUT,
	OUTPUT,
	HEREDOC,
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
t_token	*tokenize(char *input, t_meta *meta);
int		check_syntax(t_token *tokens);

// parsing
void	check_env_vars(t_token *tokens, t_meta *meta);
int		parse_redir(t_node *node, t_token *tokens, int i, t_meta *meta);
int		parse_quotes(token_type quote, t_token *tokens, int *i);
int		parse(char *input, t_meta *meta);

// utils
void	skip_space_redirs(int *i, t_token *tokens);
void	get_args(int *i, t_node *node, t_token *tokens);
void	remove_token(t_token *tokens, int i);
void	merge_tokens(int start, t_token *tokens, token_type end_token);
void	free_tokens(t_token	*tokens);

// printing
void	print_list(t_list **head);
t_node	*init_node(char *command);
void	print_node(t_node *node);

#endif
