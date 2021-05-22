/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:06:07 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/03 13:02:16 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*ar;
	size_t			i;

	i = 0;
	ar = (unsigned char *)arr;
	while (i < n)
	{
		if (ar[i] == (unsigned char)c)
			return (ar + i);
		else
			i++;
	}
	return (NULL);
}
