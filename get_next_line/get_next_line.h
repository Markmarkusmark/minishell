/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:32:39 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/28 10:27:55 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1000

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
size_t	ft_strlen1(const char *str);
char	*ft_strjoin1(char const *s1, char const *s2);
char	*ft_strdup1(const char *s);
char	*ft_strchr1(const char *str, int c);

#endif
