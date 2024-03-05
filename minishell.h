/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/03/05 15:31:26 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "executing/executing.h"
# include "parsing/parsing.h"
# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
    char    *command; // just the command/builtin - no path
    char    **arguments; // array for execve
    char    *infile; // NULL if not existing
    char    *outfile; // NULL if not existing
    int     append; // 1 is true, 0 is false
    int     pipe_to_next; // as above
    int     pipe_from_prev; // as above
    struct s_node  *next;
}   t_node;

// FUNCTIONS
// Elise

// Marc

#endif

// check path as part of execution
