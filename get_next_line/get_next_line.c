/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:29:20 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/29 16:43:42 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_func(char **line, char **buff, int bytes)
{
	char	*end;
	char	*tmp;

	if (!bytes && !*buff)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((end = ft_strchr(*buff, '\n')))
	{
		*end = '\0';
		*line = ft_strdup(*buff);
		tmp = ft_strdup(++end);
		free(*buff);
		*buff = tmp;
	}
	else
	{
		*line = *buff;
		*buff = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*remainder;
	int			get_bytes;
	char		*buffer;
	char		*tmp;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || (read(fd, 0, 0) < 0) ||
			(!(buffer = (char *)malloc(BUFFER_SIZE + 1))))
		return (-1);
	while ((get_bytes = read(fd, buffer, BUFFER_SIZE)))
	{
		if (get_bytes == -1)
		{
			free(remainder);
			return (-1);
		}
		buffer[get_bytes] = '\0';
		tmp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		free(tmp);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	free(buffer);
	return (ft_check_func(line, &remainder, get_bytes));
}
