/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/04/24 15:04:51 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../src/libft/libft.h"
# include "../src/libft/getnextline.h"
# include "../src/libft/ft_printf.h"
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
# define ERR_SYNT "Syntax error\n"
# define ERR_ARGS "too many arguments"
# define ERR_NUM ": numeric argument required"

typedef struct s_node
{
	char	*command; // just the command/builtin - no path
	char	*path; // comand inc path
	char	**args; // array for execve
	char	**infile; // NULL if not existing, should be come a list of files
	char	**outfile; // NULL if not existing
	char	**heredoc; // string contains delimiter given to heredoc
	int		*append; // 1 is true, 0 is false
	int		*fd_in;
	int		*fd_out;
	int		**hd_pipe;
	int		n_input;
	int		n_output;
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
void	free_meta(t_meta *meta);
void	free_matrix(char **matrix);

#endif


