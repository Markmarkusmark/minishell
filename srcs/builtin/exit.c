/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:22:33 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 15:25:44 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_exit(char *arg, t_msh *msh)
{
	int	checker;
	int	i;

	checker = 0;
	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			checker = -1;
		}
		i++;
	}
	if (checker == -1)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("command \"exit\": numeric argument required\n", 2);
		msh->return_code = 255;
		exit(255);
	}
}

void	ft_exit(t_msh *msh, t_com *com)
{
	int	n;

	if (com->args_new == NULL)
	{
		msh->return_code = 0;
		ft_putstr_fd("exit", 1);
		exit(0);
	}
	else if (com->args_new[1] != NULL)
	{
		ft_putstr_fd("exit", 1);
		ft_putstr_fd("command \"exit\" shouldn't get more than 1 argument\n", 2);
		msh->return_code = 1;
	}
	else
	{
		ft_check_exit(com->args_new[0], msh);
		n = ft_atoi(com->args_new[0]);
		while (n > 256)
			n = n % 256;
		msh->return_code = n;
		ft_putstr_fd("exit", 1);
		exit(n);
	}
}
