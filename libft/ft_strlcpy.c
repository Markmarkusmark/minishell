/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:57:38 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/08 14:13:20 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (ft_strlen(src));
}
