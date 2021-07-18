/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 09:53:46 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 11:22:09 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_quote_flag(t_msh *msh, const int *i, int q_flag)
{
	if (msh->str[*i] == '\'' && q_flag != 2)
	{
		if (q_flag == 0)
			q_flag = 1;
		else if (q_flag == 1)
			q_flag = 0;
	}
	else if (msh->str[*i] == '"' && q_flag != 1)
	{
		if (q_flag == 0)
			q_flag = 2;
		else if (q_flag == 2)
			q_flag = 0;
	}
	return (q_flag);
}

int	ft_check_open_quote(int q_flag)
{
	if (q_flag == 1)
	{
		ft_putstr_fd("open single quote\n", 1);
		return (-1);
	}
	if (q_flag == 2)
	{
		ft_putstr_fd("open double quote\n", 1);
		return (-1);
	}
	return (0);
}

int	ft_line_size_utils(t_msh *msh, int *i, int q_flag)
{
	if (msh->str[*i] == '\\' && (q_flag == 0 || (q_flag == 2
				&& (msh->str[*i + 1] == '$'
					|| msh->str[*i + 1] == '\\'
					|| msh->str[*i + 1] == '"'))))
	{
		(*i)++;
		if (msh->str[*i] == '\0')
		{
			ft_putstr_fd("open backslash\n", 1);
			return (0);
		}
	}
	return (1);
}

int	ft_line_size(t_msh *msh)
{
	int	q_flag;
	int	i;
	int	str_len;
	int	err;

	q_flag = 0;
	i = -1;
	str_len = 0;
	while (msh->str[++i])
	{
		q_flag = ft_get_quote_flag(msh, &i, q_flag);
		if (!ft_line_size_utils(msh, &i, q_flag))
			return (-1);
		str_len++;
	}
	err = ft_check_open_quote(q_flag);
	if (err != 0)
		return (-1);
	else
		return (str_len);
}

int	ft_preparser(t_msh *msh)
{
	int	str_len;

	str_len = ft_line_size(msh);
	if (str_len == -1)
	{
		msh->return_code = 1;
		return (1);
	}
	msh->line = ft_get_struct_line(msh, str_len);
	if (!msh->line)
		close_prog("line malloc error\n");
	ft_lstadd_front(&g_mem, ft_lstnew(msh->line));
	if (ft_get_dollar(msh) == 0)
		return (1);
	if (ft_check_line_syntax(msh))
	{
		msh->return_code = 258;
		free(msh->line);
		return (1);
	}
	return (0);
}
