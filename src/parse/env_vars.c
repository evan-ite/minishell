/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:24:45 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/01 18:01:50 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	handle_exit_codes(t_token *tokens, t_meta *meta, int i);

void	handle_var(t_token *tokens, int i, t_meta *meta)
{
	char	*var;

	var = NULL;
	if (!tokens[i + 1].value)
	{
		tokens[i].type = WORD;
		return ;
	}
	if (tokens[i + 1].type == WORD && !ft_strncmp("?", tokens[i + 1].value, 1))
	{
		handle_exit_codes(tokens, meta, i);
		return ;
	}
	if (tokens[i + 1].type == WORD)
		var = get_envar(meta, tokens[i + 1].value);
	if (var)
	{
		free(tokens[i + 1].value);
		tokens[i + 1].value = ft_strdup(var);
		remove_token(tokens, i);
	}
	else if (tokens[i + 1].type == WORD)
	{
		remove_token(tokens, i + 1);
		remove_token(tokens, i);
	}
	else
		tokens[i].type = WORD;
}



/*
Iterates through the input to find environment variables to expand*/
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

/*
attempts to find tofind in the envvars. Search is Case sensitive.
If found, returns a pointer the to value, otherwise returns NULL*/
char	*get_envar(t_meta *meta, char *tofind)
{
	int	i;

	i = 0;
	if (!tofind || !meta || !meta->envp)
		return (NULL);
	while (meta->envp[i])
	{
		if (!ft_strncmp(meta->envp[i], tofind, ft_strlen(tofind)))
		{
			if (*(meta->envp[i] + ft_strlen(tofind)) == '=')
				return (meta->envp[i] + ft_strlen(tofind) + 1);
		}
		i++;
	}
	return (NULL);
}

void	handle_exit_codes(t_token *tokens, t_meta *meta, int i)
{
	char	*temp;
	char	*exit_code;

	if (ft_strlen(tokens[i + 1].value) == 1)
	{
		free(tokens[i + 1].value);
		tokens[i + 1].value = ft_itoa(meta->exit_code);
		remove_token(tokens, i);
		return ;
	}
	exit_code = ft_itoa(meta->exit_code);
	if (!exit_code)
		exit_error(NULL, NULL, meta->exit_code, meta);
	temp = ft_strdup(tokens[i + 1].value + 1);
	if (!temp)
		exit_error(NULL, NULL, meta->exit_code, meta);
	free(tokens[i + 1].value);
	tokens[i + 1].value = ft_strjoin(exit_code, temp);
	free(exit_code);
	free(temp);
	remove_token(tokens, i);
}
