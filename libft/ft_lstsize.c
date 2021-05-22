/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:34:45 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/11 18:39:06 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_lstsize(t_list *lst)
{
	unsigned int	size;

	size = 0;
	while (lst != 0)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
