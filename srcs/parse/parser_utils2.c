/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:04:18 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 10:31:30 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_line_symbol	*ft_mshdup(t_line_symbol *line)
{
	int				i;
	int				len;
	t_line_symbol	*dup_line;

	len = ft_mshstrlen(line);
	if (!line)
		return (NULL);
	dup_line = malloc((len + 1) * sizeof(t_line_symbol *));
	if (!dup_line)
		return (NULL);
	ft_lstadd_front(&g_mem, ft_lstnew(dup_line));
	i = 0;
	while (line[i].symb)
	{
		dup_line[i] = line[i];
		i++;
	}
	dup_line[i].symb = '\0';
	return (dup_line);
}

void	ft_skip_spaces_in_line(t_msh *msh, int *i)
{
	while (msh->line[*i].symb == ' ' && msh->line[*i].flag == 0)
		(*i)++;
}

void	ft_split_line(t_msh *msh, t_com *command, int *i)
{
	if (ft_get_args(msh, command, i))
		ft_exit(msh, command);
	if (ft_get_command(command))
		ft_exit(msh, command);
}

void	ft_init_proc(t_com **command, t_list **new_list)
{
	*command = malloc(sizeof(t_com));
	if (!*command)
		close_prog("malloc error\n");
	ft_lstadd_front(&g_mem, ft_lstnew(*command));
	*new_list = ft_lstnew(*command);
	if (!*new_list)
		close_prog("malloc error\n");
	ft_lstadd_front(&g_mem, ft_lstnew(*new_list));
	(*command)->pipe_out = '-';
	(*command)->pipe_in = '-';
	(*command)->com = NULL;
	(*command)->args = NULL;
	(*command)->args_new = NULL;
}

void	ft_get_separator(t_msh *msh, t_com *command, int separ, int *i)
{
	if (separ == 1)
	{
		if (((msh->line[*i].symb == '|') || (msh->line[*i].symb == ';'))
			&& msh->line[*i].flag == 0)
			command->pipe_in = msh->line[*i].symb;
	}
	if (separ == 0)
	{
		if (((msh->line[*i].symb == '|') || (msh->line[*i].symb == ';'))
			&& msh->line[*i].flag == 0)
		{
			command->pipe_out = msh->line[*i].symb;
			(*i)++;
		}
	}
}
