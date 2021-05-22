/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:32:08 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/29 17:18:29 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return ((ft_strdup(s2)));
	string = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!string)
		return (NULL);
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		string[i++] = s2[j++];
	}
	string[i] = '\0';
	return (string);
}

size_t	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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
