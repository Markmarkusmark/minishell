/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:03:25 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/04 19:44:49 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	m;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * (-1);
	}
	m = (unsigned int)n;
	if (m >= 10)
	{
		ft_putnbr_fd(m / 10, fd);
	}
	ft_putchar_fd(m % 10 + '0', fd);
}
