/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 12:14:47 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 12:56:04 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("");
		rl_on_new_line();
		rl_redisplay();
	}
}

char 	**ft_get_envs(t_msh *msh)
{
	t_list	*list;
	char	**envs;
	int		i;
	int		j;

	i = ft_lstsize(msh->env);
	envs = malloc((i + 1) * sizeof(char *));
	j = 0;
	list = msh->env;
	while (list)
	{
		if (((t_env *)list->content)->val)
		{
			if (!ft_get_envs_values((t_env *)list->content, &envs[j]))
				return (NULL);
			j++;
		}
		list = list->next;
	}
	envs[j] = NULL;
	return (envs);
}
