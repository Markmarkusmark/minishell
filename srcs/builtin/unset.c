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

// void	ft_unset(t_msh *msh, t_com *com)
// {
// 	int		i;
// 	t_env	envp;
// 	t_env	*temp;
// 	t_list	*lst;

// 	i = 0;
// 	if (com->args_new[i] != NULL)
// 	{
// 		msh->env_args = ft_split(com->args_new[i], '=');
// 		envp.key = msh->env_args[0];
// 		envp.val = msh->env_args[1];
// 		lst = msh->env;
// 		while (lst)
// 		{
// 			temp = lst->content;
// 			if (strcmp(temp->key, envp.key) == 0)
// 				break ;
// 			lst = lst->next;
// 		}
// 		ft_lstdel(lst, msh->env);
// 	}
// 	return ;
// }

void	del_lst(void *env)
{
	free(((t_env *)env)->key);
	free(((t_env *)env)->val);
	free((t_env *)env);
}

void	unsetter(t_msh *msh, char **args_str, int *i)
{
	t_list	*prev;
	t_list	*list;

	list = msh->env;
	while (list)
	{
		if (!ft_strcmp(((t_env *)list->content)->key, args_str[*i]))
		{
			if (list == msh->env)
			{
				msh->env = list->next;
				ft_lstdelone(list, &del_lst);
			}
			else
			{
				prev->next = list->next;
				ft_lstdelone(list, &del_lst);
			}
			break ;
		}
		prev = list;
		list = list->next;
	}
}

int	unset_errors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("unset : not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
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
		if (!unset_errors(com->args_new[i]))
		{
			i++;
			msh->return_code = 1;
			continue ;
		}
		unsetter(msh, com->args_new, &i);
		i++;
	}
}