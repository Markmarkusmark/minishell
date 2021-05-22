/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:27:28 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/11 21:13:19 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		if (del)
		{
			del(current->content);
		}
		free(current);
		current = next;
	}
	*lst = 0;
}
