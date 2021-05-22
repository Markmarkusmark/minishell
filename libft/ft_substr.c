/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:44:55 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/10 18:30:45 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	substr = (char *)malloc((sizeof(*s) * (len + 1)));
	if (!substr)
		return (NULL);
	s_len = 0;
	sub_len = 0;
	while (s[s_len])
	{
		if (s_len >= start && sub_len < len)
		{
			substr[sub_len] = s[s_len];
			sub_len++;
		}
		s_len++;
	}
	substr[sub_len] = '\0';
	return (substr);
}
