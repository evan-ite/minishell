/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:30:48 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/16 11:28:31 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	free_array(void **array, int len)
/*
char **array:	the allocated array that should be freed
int len:		an optional integer with the length of the array
				that should be freed. If len < 0 array will be
				freed until NULL pointer */
{
	int	i;

	if (!array)
		return ;
	i = 0;
	if (len < 0)
	{
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			if (array[i])
				free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
	free(array);
	array = NULL;
}
