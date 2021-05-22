/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:50:44 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/11 19:11:16 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elemenet;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_elemenet = ft_lstlast(*lst);
	last_elemenet->next = new;
}
