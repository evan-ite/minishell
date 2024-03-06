/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/03/06 11:58:10 by evan-ite         ###   ########.fr       */
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

t_token	*tokenize(char *input);
void	parse(char *input, t_node **cmnd_lst);

#endif

