/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:38:00 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 16:43:08 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	ft_lstsort_utils(t_sort *sort, t_list *sorted, t_list *lst, t_list *beg)
// {
// 	sort->i = 0;
// 	sorted = malloc(sizeof(t_list));
// 	ft_copy_lst(lst, &sorted);
// 	sort->j = ft_lstsize(sorted);
// 	beg = sorted;
// }

// void	ft_lstsort(t_list *lst)
// {
// 	t_list	*beg;
// 	t_list	*sorted;
// 	t_env	*elem1;
// 	t_env	*elem2;
// 	t_sort	sort;

// 	beg = NULL;
// 	sorted = NULL;
// 	ft_lstsort_utils(&sort, sorted, lst, beg);
// 	while (sort.i < sort.count - 1)
// 	{
// 		sort.j = 0;
// 		sorted = beg;
// 		while (sort.j < sort.count - sort.i - 1)
// 		{
// 			elem1 = sorted->content;
// 			elem2 = sorted->next->content;
// 			if (ft_strcmp(elem1->key, elem2->key) > 0)
// 			{
// 				sorted->content = (t_env *)elem2;
// 				sorted->next->content = (t_env *)elem1;
// 			}
// 			sorted = sorted->next;
// 			sort.j++;
// 		}
// 		sort.i++;
// 	}
// 	ft_print_env(sorted, 1, 1);
// }

void ft_lstsort(t_list *lst)
{
	t_list *sorted;
	t_list *beg;
	t_env *elem1;
	t_env *elem2;
	int count;
	int i, j;

	count = 1;
	i = 0;
	sorted = malloc(sizeof(t_list)); // error
	ft_copy_lst(lst, &sorted);
	count = ft_lstsize(sorted);
	beg = sorted;
	while (i < count - 1)
	{
		j = 0;
		sorted = beg;
		while (j < count - i - 1)
		{
			elem1 = sorted->content;
			elem2 = sorted->next->content;
			if (ft_strcmp(elem1->key, elem2->key) > 0)
			{
				sorted->content = (t_env *)elem2;
				sorted->next->content = (t_env *)elem1;
			}
			sorted = sorted->next;
			j++;
		}
		i++;
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

int	ft_export_check(char **args)
{
	int		i;
	char	c;

	i = 0;
	c = args[0][0];
	if ((ft_isalpha(c) == 0) && c != '_')
	{
		ft_putstr_fd("wrong export \n", 2);
		return (1);
	}
	while (args[0][i] != '\0')
	{
		if (ft_isenv(args[0][i]) == 0)
		{
			ft_putstr_fd("wrong export \n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export_utils(t_msh *msh)
{
	

	ft_lstsort(msh->env);
}

int	ft_export(t_msh *msh, t_com *com)
{
	int		i;
	t_env	*envp;

	i = 0;
	if (com->args_new == NULL)
	{
		ft_export_utils(msh);
	}
	else
	{
		while (com->args_new[i])
		{
			envp = malloc(sizeof(t_env));
			msh->env_args = ft_split(com->args_new[i], '=');
			if (ft_export_check(msh->env_args) == 0)
			{
				envp->key = msh->env_args[0];
				envp->val = msh->env_args[1];
				ft_lstadd_back(&msh->env, ft_lstnew(envp));
			}
			free(msh->env_args);
			i++;
		}
	}
	return (0);
}