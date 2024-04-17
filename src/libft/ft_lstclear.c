/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:50:07 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/07 14:26:55 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst || !lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	free(*lst);
}
