/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/04/10 12:00:11 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include "../libft/getnextline.h"
# include "../libft/ft_printf.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_CMND ": Command not found"
# define ERR_PIPE "Error creating pipe"
# define ERR_CHILD "Error creating child"
# define ERR_MEM "Error allocating memory"
# define ERR_FILE ": No such file in directory"
# define ERR_FPER ": Permission denied"
# define ERR_SYNT "Syntax error"

typedef struct s_node
{
	char	*command; // just the command/builtin - no path
	char	*path; // comand inc path
	char	**args; // array for execve
	char	*infile; // NULL if not existing, should be come a list of files
	int		fd_in;
	char	*outfile; // NULL if not existing
	int		fd_out;
	int		append; // 1 is true, 0 is false
	char	*heredoc; // string contains delimiter given to heredoc
	int		pipe_to_next; // as above
	int		pipe_from_prev; // as above
}	t_node;

typedef struct s_meta
{
	int		n_cmnds;
	int		*pid;
	int		**pipe;
	char	**envp;
	int		exit_code;
	t_list	**cmnd_lst;
}	t_meta;


// Error handling
int		exit_error(char *err_msg, char *src, int err_code, t_meta *meta);
void	free_list(t_list **cmnd_list);

#endif

