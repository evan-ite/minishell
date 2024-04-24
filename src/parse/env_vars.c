/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:24:45 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/24 16:50:31 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	handle_var(t_token *tokens, int i, t_meta *meta)
{
	char	*var;

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
		var = get_envar(meta, tokens[i + 1].value);
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
		remove_token(tokens, i + 1);
		remove_token(tokens, i);
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

char	*get_envar(t_meta *meta, char *tofind)
{
	int	i;

	i = 0;
	if (!tofind)
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
