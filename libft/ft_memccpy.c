/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:06:00 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/03 13:05:53 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char*)destination;
	src = (unsigned char*)source;
	i = 0;
	while (i < n && src[i] != (unsigned char)c)
	{
		dest[i] = src[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		dest[i] = src[i];
		i++;
		return (&dest[i]);
	}
}
