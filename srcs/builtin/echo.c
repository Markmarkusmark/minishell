/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:06:48 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 15:06:52 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_n(t_com *com, int *a)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	b = 0;
	while (i < com->num_args && !ft_strncmp(com->args_new[i], "-n", 2))
	{
		j = 1;
		while (com->args_new[i][j] == 'n')
			j++;
		if (com->args_new[i][j] == '\0')
		{
			*a = i + 1;
			b = 1;
		}
		else
		{
			*a = i;
			break ;
		}
		i++;
	}
	return (b);
}

void	ft_echo(t_msh *msh, t_com *com)
{
	int	num;
	int	n;

	if (com->args_new == NULL)
	{
		ft_putstr_fd("\n", 1);
		msh->return_code = 0;
		return ;
	}
	num = 0;
	n = ft_check_n(com, &num);
	while (num < com->num_args)
	{
		ft_putstr_fd(com->args_new[num], 1);
		if (num < com->num_args - 1)
			ft_putstr_fd(" ", 1);
		num++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	msh->return_code = 0;
}
