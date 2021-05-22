/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:35:48 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/10 18:28:33 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*string;

	if (!s1 || !s2)
		return (ft_strdup(""));
	string = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (*s1)
	{
		string[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		string[i] = *s2;
		i++;
		s2++;
	}
	string[i] = '\0';
	return (string);
}
