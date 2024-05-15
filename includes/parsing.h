/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/05/15 21:20:00 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include <stdio.h>

typedef enum s_types
{
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
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

// tokenizing and parsing
t_token	*tokenize(char *input, t_meta *meta);
int		check_syntax(t_token *tokens);

// parsing
void	check_env_vars(t_token *tokens, t_meta *meta);
int		parse_redir(t_node *node, t_token *tokens, int i, t_meta *meta);
int		parse_quotes(t_token_type quote, t_token *tokens, int *i, t_meta *meta);
int		parse(char *input, t_meta *meta);
void	handle_var(t_token *tokens, int i, t_meta *meta);

// utils
void	skip_space_redirs(int *i, t_token *tokens);
void	get_args(int *i, t_node *node, t_token *tokens);
void	remove_token(t_token *tokens, int i);
void	merge_tokens(int start, t_token *tokens, t_token_type end_token);
void	free_tokens(t_token	*tokens);
char	*get_envar(t_meta *meta, char *tofind);
int		check_quotes(t_token *tokens, t_meta *meta);
int		syntax_error(t_meta *meta, t_token *tokens);
void	merge_words(int start, t_token *tokens);

// tokenize utils
int		tokencount(char *input);
int		is_special(char c);

// printing
void	print_list(t_list **head);
t_node	*init_node(char *command);
void	print_node(t_node *node);

// syntax utils
void	skip_spaces(int *i, t_token *tokens);
int		is_redir(t_token token);

#endif
