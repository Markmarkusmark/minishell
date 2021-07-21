/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:04:04 by mryan             #+#    #+#             */
/*   Updated: 2021/07/21 20:45:32 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void 	ft_launch_com_utils(t_msh *msh, char *buff, char **argv)
{
	if (buff == NULL)
	{
		dup2(msh->fd_1, 1);
		ft_putstr_fd("command not found in the paths\n", 2);
		free_arr(argv);
		msh->return_code = 127;
		return ;
	}
	ft_exec_com(msh, argv, buff);
	free_arr(argv);
}

int	ft_shlvl_check(char *shlvl)
{
	int	i;

	i = 0;
	while (shlvl[i])
	{
		if (ft_isdigit(shlvl[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_launch_extra_utils(int f, t_msh *msh)
{
	t_env	*env_tmp;

	if (f == 0)
	{
		env_tmp = malloc(sizeof(t_env));
		env_tmp->key = "SHLVL";
		env_tmp->val = "1";
		ft_lstadd_back(&msh->env, ft_lstnew(env_tmp));
	}
}

void	ft_launch_extra_utils_2(t_env *env_tmp)
{
	int		temp;

	if (ft_shlvl_check(env_tmp->val) == 0)
	{
		temp = ft_atoi(env_tmp->val) + 1;
		free(env_tmp->val);
		env_tmp->val = ft_itoa(temp);
	}
	else
	{
		free(env_tmp->val);
		env_tmp->val = ft_itoa(1);
	}
}
