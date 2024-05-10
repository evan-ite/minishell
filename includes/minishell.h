/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:41:39 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/05/10 20:20:04 by tsurma           ###   ########.fr       */
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

# define ERR_CMND ": command not found"
# define ERR_PIPE "Error creating pipe"
# define ERR_CHILD "Error creating child"
# define ERR_MEM "Error allocating memory"
# define ERR_FILE ": No such file or directory"
# define ERR_FPER ": Permission denied"
# define ERR_SYNT "Syntax error"
# define ERR_ARGS " too many arguments"
# define ERR_NUM ": numeric argument required"
# define ERR_DIR ": Is a directory"
# define ERR_PERM " Permission denied"

extern int	g_sig;

typedef struct s_node
{
	char	*command;
	char	*path;
	char	**args;
	char	**infile;
	char	**outfile;
	char	**heredoc;
	int		*append;
	int		*fd_in;
	int		*fd_out;
	int		**hd_pipe;
	int		n_input;
	int		n_output;
	int		pipe_to_next;
	int		pipe_from_prev;
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
void	sigint_handler(int sig);

#endif
