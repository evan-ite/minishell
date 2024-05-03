/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:30:48 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/03 16:55:00 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static void	free_no_len(void **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

/*
char ***array:	the allocated *array that should be freed
int len:		an optional integer with the length of the *array
				that should be freed. If len < 0 *array will be
				freed until NULL pointer */
void	free_array(void **array, int len)
{
	int	i;

	if (!array)
		return ;
	if (len < 0)
		free_no_len(array);
	else
	{
		i = 0;
		while (i < len)
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
	}
	free(array);
	array = NULL;
}
