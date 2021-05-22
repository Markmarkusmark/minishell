/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:57:38 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/03 13:40:55 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char*)str);
}
