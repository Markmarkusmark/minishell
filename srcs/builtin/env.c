/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:29:42 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 15:31:30 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env(t_list *env, int fd, int declare)
{
	t_env	*envp;

	while (env)
	{
		envp = malloc(sizeof(t_env));
		ft_lstadd_front(&g_mem, ft_lstnew(envp));
		envp = env->content;
		if (declare == 1)
			write(fd, "declare -x ", 11);
		write(fd, envp->key, strlen(envp->key));
		write(fd, "=", 1);
		if (envp->val != NULL)
			write(fd, envp->val, strlen(envp->val));
		write(fd, "\n", 1);
		env = env->next;
	}
}

void	ft_env(t_msh *msh, t_com *com)
{
	if (com->args_new == NULL)
		ft_print_env(msh->env, 1, 0);
	else
	{
		ft_putstr_fd("command \"env\" shouldnt get arguments\n", 2);
		msh->return_code = 1;
		return ;
	}
	msh->return_code = 0;
}
