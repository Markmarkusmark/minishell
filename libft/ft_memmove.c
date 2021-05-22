/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:57:38 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/10 18:27:12 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			n;

	n = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (NULL);
	if (source < dest)
	{
		while (len--)
			dest[len] = source[len];
	}
	else
	{
		while (n < len)
		{
			dest[n] = source[n];
			n++;
		}
	}
	return (dst);
}
