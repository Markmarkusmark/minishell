/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:53:53 by mryan             #+#    #+#             */
/*   Updated: 2021/07/21 20:57:29 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export_utils_2(t_msh *msh, int *f)
{
	t_list	*tmp;
	t_env	*env_tmp;

	tmp = msh->env;
	while (tmp)
	{
		env_tmp = tmp->content;
		if (ft_strcmp(env_tmp->key, msh->env_args[0]) == 0)
		{
			free(env_tmp->val);
			env_tmp->val = ft_strdup(msh->env_args[1]);
			free(msh->env_args[0]);
			free(msh->env_args[1]);
			*f = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_export_utils(t_msh *msh, t_env *envp)
{
	int		f;

	f = 0;
	ft_export_utils_2(msh, &f);
	if (f == 0)
	{
		if (ft_export_check(msh->env_args, msh) == 0)
		{
			envp->key = msh->env_args[0];
			envp->val = msh->env_args[1];
			ft_lstadd_back(&msh->env, ft_lstnew(envp));
			msh->return_code = 0;
		}
	}
}
