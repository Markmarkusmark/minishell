/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:33:48 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 15:36:04 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(t_msh *msh, t_com *com)
{
	int		i;
	t_env	envp;
	t_env	*temp;
	t_list	*lst;

	i = 0;
	if (com->args_new[i] != NULL)
	{
		msh->env_args = ft_split(com->args_new[i], '=');
		envp.key = msh->env_args[0];
		envp.val = msh->env_args[1];
		lst = msh->env;
		while (lst)
		{
			temp = lst->content;
			if (strcmp(temp->key, envp.key) == 0)
				break ;
			lst = lst->next;
		}
		ft_lstdel(lst, msh->env);
	}
	return ;
}
