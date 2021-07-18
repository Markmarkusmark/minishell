/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 10:20:45 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 10:22:49 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_val_in_dlr_init(t_line_symbol *line, int *val_i, char **val)
{
	*val_i = 0;
	while (((ft_isalnum(line[*val_i].symb) == 1) || line[*val_i].symb == '_')
		   && line[*val_i].flag == 0)
		(*val_i)++;
	(*val) = malloc((*val_i) + 1);
	if (!(*val))
		return (-1);
	ft_lstadd_front(&g_mem, ft_lstnew((*val)));
	return (0);
}

int	ft_get_val_in_dlr(t_msh *msh, t_line_symbol *line)
{
	int		val_i;
	char	*val;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (ft_get_val_in_dlr_init(line, &val_i, &val) == -1)
		return (-1);
	while (++i < val_i)
	{
		val[i] = line[j].symb;
		j++;
	}
	val[i] = '\0';
	if (line[0].symb == '?')
	{
		msh->val_in_dlr = ft_itoa(msh->return_code);
		val_i++;
		if (!msh->val_in_dlr)
			return (-1);
	}
	else
		msh->val_in_dlr = ft_get_env(msh, val);
	return (val_i);
}

int	ft_envir(t_msh *msh, int i, int j)
{
	t_line_symbol	*s1;
	t_line_symbol	*s2;
	t_line_symbol	*s3;
	t_line_symbol	*new_line;

	new_line = ft_get_new_line(msh);
	if (!new_line)
		return (0);
	s1 = ft_mshsubstr(msh, i - 1);
	if (!s1)
		return (0);
	s2 = ft_mshstrjoin(s1, new_line);
	if (!s2)
		return (0);
	s3 = ft_mshstrjoin(s2, &msh->line[j]);
	if (!s3)
		return (0);
	if (msh->line[i].symb == '?')
		free(msh->val_in_dlr);
	free(msh->line);
	msh->line = s3;
	free(s1);
	free(s2);
	free(new_line);
	return (1);
}

int	ft_get_dollar_utils(t_msh *msh, int	*beg, int *end_str, int *val)
{
	*val = ft_get_val_in_dlr(msh, &msh->line[*beg]);
	if (*val == -1)
		return (0);
	*end_str = *beg + *val;
	return (1);
}

int	ft_get_dollar(t_msh *msh)
{
	int	beg;
	int	end_str;
	int	val;

	beg = -1;
	end_str = 0;
	val = 0;
	while (msh->line[++beg].symb)
	{
		if (msh->line[beg].symb == '$' && msh->line[beg].flag == 0)
		{
			beg++;
			if (((ft_isalnum(msh->line[beg].symb) == 0)
					&& msh->line[beg].symb != '_' && msh->line[beg].symb != '?')
				|| msh->line[beg].flag == 1)
				continue ;
			if (!ft_get_dollar_utils(msh, &beg, &end_str, &val))
				return (0);
			if (ft_check(msh, beg, end_str) == 1)
				return (0);
			beg = beg - 2;
		}
	}
	return (1);
}
