/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:24:45 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/16 17:10:36 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	check_squote(t_token *tokens, int i)
{
	int		j;
	int		squote;

	j = 0;
	squote = 0;
	while (tokens[j].value)
	{
		if (tokens[j].type == SQUOTE)
		{
			if (j < i && squote == 0)
				squote = 1;
			else if (j < i && squote == 1)
				squote = 0;
			else if (j > i && squote == 1)
				break ;
		}
		j++;
	}
	return (squote);
}

static void	handle_var(t_token *tokens, int i, t_meta *meta)
{
	char	*var;
	int		squote;

	squote = check_squote(tokens, i);
	if (!squote)
	{
		if (!tokens[i + 1].value)
		{
			tokens[i].type = WORD;
			return ;
		}
		if (tokens[i + 1].type == WORD && !ft_strcmp("?", tokens[i + 1].value))
		{
			free(tokens[i + 1].value);
			tokens[i + 1].value = ft_itoa(meta->exit_code);
			remove_token(tokens, i);
			return ;
		}
		if (tokens[i + 1].type == WORD)
			var = getenv(tokens[i + 1].value);
		else
			var = NULL;
		if (var)
		{
			free(tokens[i + 1].value);
			tokens[i + 1].value = ft_strdup(var);
			remove_token(tokens, i);
		}
		else if (tokens[i + 1].type == WORD)
		{
			tokens[i].type = WORD;
			free(tokens[i].value);
			tokens[i].value = ft_strjoin("$", tokens[i + 1].value);
			tokens[i + 1].type = SSPACE;
			free(tokens[i + 1].value);
			tokens[i + 1].value = ft_strdup(" ");
		}
		else
			tokens[i].type = WORD;
	}
	else
		tokens[i].type = WORD;
}

void	check_env_vars(t_token *tokens, t_meta *meta)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == DOLLAR)
			handle_var(tokens, i, meta);
		i++;
	}
}
