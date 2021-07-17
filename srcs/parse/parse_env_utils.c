/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 10:20:37 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 10:22:31 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_symbol_flag_utils(t_msh *msh, const int *i, int qte)
{
	if (!qte || (qte == 2 && (msh->str[*i + 1] == '$' || msh->str[*i + 1] == '\\'
				|| msh->str[*i + 1] == '"')))
		return (1);
	return (0);
}

char 	*ft_get_env(t_msh *msh, char *val)
{
	t_list	*list;

	list = msh->env;
	while (list)
	{
		if (!ft_strcmp(val, ((t_env *)list->content)->key))
			return (((t_env *)list->content)->val);
		list = list->next;
	}
	return (NULL);
}

int	ft_notenv(t_msh *msh, int i, int j)
{
	t_line_symbol	*s1;
	t_line_symbol	*s2;

	s1 = ft_mshsubstr(msh, i - 1);
	if (!s1)
		return (0);
	s2 = ft_mshstrjoin(s1, &msh->line[j]);
	if (!s2)
		return (0);
	free(msh->line);
	msh->line = s2;
	free(s1);
	return (1);
}

t_line_symbol	*ft_get_new_line(t_msh *msh)
{
	int				i;
	t_line_symbol	*new_line;
	int				len;

	i = -1;
	len = (int) ft_strlen(msh->val_in_dlr) + 1;
	new_line = malloc(sizeof (t_line_symbol) * len);
	if (!new_line)
		return (NULL);
	while (msh->val_in_dlr[++i])
	{
		new_line[i].symb = msh->val_in_dlr[i];
		new_line[i].flag = 1;
	}
	new_line[i].symb = '\0';
	return (new_line);
}

int	ft_check(t_msh *msh, int begin_str, int end_str)
{
	if (msh->val_in_dlr)
	{
		if (ft_envir(msh, begin_str, end_str) == 0)
			return (1);
	}
	else
	{
		if (ft_notenv(msh, begin_str, end_str) == 0)
			return (1);
	}
	return (0);
}
