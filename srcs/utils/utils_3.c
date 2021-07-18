/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 12:14:47 by mryan             #+#    #+#             */
/*   Updated: 2021/07/18 12:06:07 by mryan            ###   ########.fr       */
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
	if (!envs)
		close_prog("malloc error\n");
	ft_lstadd_front(&g_mem, ft_lstnew(envs));
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

void	ft_file_check_utils(t_msh *msh, t_rdr rdr, int rdr_num, int *fd)
{
	if (!ft_strcmp(rdr.kind, "<"))
	{
		msh->rdr_type[0] = rdr_num;
		*fd = open(rdr.arg, O_RDONLY);
		close(*fd);
	}
	else if (!ft_strcmp(rdr.kind, "<<"))
		msh->rdr_type[0] = rdr_num;
}

int	ft_get_token_utils(t_msh *msh, int *len)
{
	if (ft_check_token2(msh, len))
		return (1);
	if ((msh->line[*len].symb == '>' || msh->line[*len].symb == '<')
		&& msh->line[*len].flag == 0)
	{
		ft_putstr_fd(
			"syntax error near unexpected token 'redirect'\n", 1);
		return (1);
	}
	return (0);
}
