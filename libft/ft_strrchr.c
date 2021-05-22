/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:57:38 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/10 18:30:24 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char*)str + i);
		i--;
	}
	return (NULL);
}
