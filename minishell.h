/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/03/05 14:41:40 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES


typedef struct s_node
{
    char    *command; // just the command/builtin - no path
    char    **arguments; // array for execve
    char    *infile; // NULL if not existing
    char    *outfile; // NULL if not existing
    int     append; // 1 is true, 0 is false
    int     pipe_to_next; // as above
    int     pipe_from_prev; // as above
    t_node  *next;
}   t_node;

// FUNCTIONS
// Elise

// Marc

#endif

// check path as part of execution