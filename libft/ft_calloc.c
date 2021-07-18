/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:35:19 by legunshi          #+#    #+#             */
/*   Updated: 2020/11/07 18:24:04 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*adress;
	int				nbytes;

	nbytes = nmemb * size;
	adress = (char *)malloc(nmemb * size);
	if (!(adress))
		return (NULL);
	else
		ft_bzero(adress, nmemb * size);
	return (adress);
}
