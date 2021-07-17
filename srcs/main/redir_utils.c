/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 09:50:47 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 13:13:08 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_redir_checker(t_com *com)
{
	int		j;
	char	*str;

	j = 0;
	while (j < com->num_args)
	{
		str = ft_get_line_from_struct(com->args[j],
				0, ft_mshstrlen(com->args[j]));
		if ((!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
				|| !ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
			&& com->args[j][0].flag == 0)
		{
			free(str);
			return (1);
		}
		free(str);
		j++;
	}
	return (0);
}

void	ft_rdr_count(t_com *com)
{
	int		j;
	char	*str;

	j = 0;
	com->num_redir = 0;
	while (j < com->num_args)
	{
		str = ft_get_line_from_struct(com->args[j],
				0, ft_mshstrlen(com->args[j]));
		if ((!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
				|| !ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
			&& com->args[j][0].flag == 0)
			com->num_redir++;
		free(str);
		j++;
	}
}

int	ft_get_result_utils(t_com *com, int num, int i)
{
	com->args_new[i] = ft_get_line_from_struct(com->args[num],
			0, ft_mshstrlen(com->args[num]));
	if (!com->args_new[i])
		return (0);
	free(com->args[num]);
	return (ITS_ARG);
}

int	ft_get_result(t_rdr *rdr, t_com *com, int num, int i)
{
	if (((ft_mshcmp(com->args[num], ">") == 0)
			|| (ft_mshcmp(com->args[num], ">>") == 0)
			|| (ft_mshcmp(com->args[num], "<") == 0)
			|| (ft_mshcmp(com->args[num], "<<") == 0))
		&& com->args[num][0].flag == 0)
	{
		rdr->type = ft_get_line_from_struct(com->args[num],
				0, ft_mshstrlen(com->args[num]));
		if (!rdr->type)
			return (0);
		rdr->file = ft_get_line_from_struct(com->args[num + 1],
				0, ft_mshstrlen(com->args[num + 1]));
		if (!rdr->file)
			return (0);
		free(com->args[num]);
		free(com->args[num + 1]);
		return (ITS_RDR);
	}
	else
		return (ft_get_result_utils(com, num, i));
}

int	ft_loop(t_rdr *rdr, t_com *com)
{
	int		i;
	int		num;
	int		rdr_num;
	int		res;

	i = 0;
	num = 0;
	rdr_num = 0;
	while (num < com->num_args)
	{
		res = ft_get_result(&rdr[rdr_num], com, num, i);
		if (res == 0)
			return (1);
		else if (res == ITS_RDR)
		{
			rdr_num++;
			num = num + 2;
		}
		else if (res == ITS_ARG)
		{
			num++;
			i++;
		}
	}
	return (0);
}
