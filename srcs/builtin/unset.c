/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:33:48 by mryan             #+#    #+#             */
/*   Updated: 2021/07/21 17:59:38 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_delete_utils(void *env)
{
	free(((t_env *)env)->key);
	free(((t_env *)env)->val);
	free((t_env *)env);
}

void	ft_delete(t_msh *msh, char **str, int *i)
{
	t_list	*previous;
	t_list	*list;

	list = msh->env;
	while (list)
	{
		if (!ft_strcmp(((t_env *)list->content)->key, str[*i]))
		{
			if (list == msh->env)
			{
				msh->env = list->next;
				ft_lstdelone(list, &ft_delete_utils);
			}
			else
			{
				previous->next = list->next;
				ft_lstdelone(list, &ft_delete_utils);
			}
			break ;
		}
		previous = list;
		list = list->next;
	}
}

int	ft_check_err(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_putstr_fd("unset : not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd("unset : not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

void	ft_unset(t_msh *msh, t_com *com)
{
	int		i;

	msh->return_code = 0;
	i = 0;
	while (i < com->num_args)
	{
		if (!ft_check_err(com->args_new[i]))
		{
			i++;
			msh->return_code = 1;
			continue ;
		}
		ft_delete(msh, com->args_new, &i);
		i++;
	}
}
