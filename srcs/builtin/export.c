/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:38:00 by mryan             #+#    #+#             */
/*   Updated: 2021/07/21 20:52:29 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sort_utils(t_list *sorted, t_env *elem1, t_env *elem2)
{
	if (ft_strcmp(elem1->key, elem2->key) > 0)
	{
		sorted->content = (t_env *)elem2;
		sorted->next->content = (t_env *)elem1;
	}
}

void	ft_lstsort(t_list *lst)
{
	t_list	*sorted;
	t_list	*beg;
	t_env	*elem1;
	t_env	*elem2;
	t_sort	sort;

	sort.count = 1;
	sort.i = -1;
	sorted = malloc(sizeof(t_list));
	ft_copy_lst(lst, &sorted);
	sort.count = ft_lstsize(sorted);
	beg = sorted;
	while (++sort.i < sort.count - 1)
	{
		sort.j = -1;
		sorted = beg;
		while (++sort.j < sort.count - sort.i - 1)
		{
			elem1 = sorted->content;
			elem2 = sorted->next->content;
			ft_sort_utils(sorted, elem1, elem2);
			sorted = sorted->next;
		}
	}
	ft_print_env(sorted, 1, 1);
}

int	ft_isenv(int c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_export_check(char **args, t_msh *msh)
{
	int		i;
	char	c;

	i = 0;
	c = args[0][0];
	if ((ft_isalpha(c) == 0) && c != '_')
	{
		ft_putstr_fd("wrong export \n", 2);
		msh->return_code = 1;
		return (1);
	}
	while (args[0][i] != '\0')
	{
		if (ft_isenv(args[0][i]) == 0)
		{
			msh->return_code = 1;
			ft_putstr_fd("wrong export \n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_msh *msh, t_com *com)
{
	int		i;
	int		args;
	t_env	*envp;

	i = 0;
	if (com->args_new == NULL)
		ft_lstsort(msh->env);
	else
	{
		args = com->num_args;
		while (args)
		{
			envp = malloc(sizeof(t_env));
			ft_lstadd_front(&g_mem, ft_lstnew(envp));
			msh->env_args = ft_split(com->args_new[i], '=');
			if (msh->env_args[0])
				ft_export_utils(msh, envp);
			free(msh->env_args);
			args--;
			i++;
		}
	}
	return (0);
}
