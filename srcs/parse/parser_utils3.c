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

int	ft_get_args(t_msh *msh, t_com *cmd, int *i)
{
	int				j;
	int				num;
	t_line_symbol	*line2;

	num = 0;
	line2 = ft_get_clean_line(msh->line);
	if (line2 == NULL)
		return (1);
	free(msh->line);
	msh->line = line2;
	while (msh->line[*i].symb == ' ' && msh->line[*i].flag == 0)
		*i = *i + 1;
	while (num < cmd->num_args)
	{
		j = ft_pass_str(i, msh);
		cmd->args[num] = ft_mshsubstr2(msh, *i, j - *i);
		if (!cmd->args[num])
			return (1);
		*i = j;
		while (msh->line[*i].symb == ' ' && msh->line[*i].flag == 0)
			*i = *i + 1;
		num++;
	}
	return (0);
}

char	*ft_get_str_from_struct(t_line_symbol *line, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	if (line[0].symb == '\0')
		return (ft_strdup(""));
	if (0 > ft_mshstrlen(line))
		return (ft_strdup(""));
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	ft_lstadd_front(&g_mem, ft_lstnew(tmp));
	while (i < len)
	{
		tmp[j] = line[i].symb;
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	ft_update_line(t_line_symbol ***str, t_com *cmd, int num, int its_cmd)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (n < cmd->num_args)
	{
		if (n == num && its_cmd == 1)
		{
			n++;
			continue ;
		}
		(*str)[i] = ft_mshdup(cmd->args[n]);
		if (!(*str)[i])
			return (1);
		free(cmd->args[n]);
		i++;
		n++;
	}
	free(cmd->args);
	cmd->args = *str;
	return (0);
}

void	ft_check_if_command(t_com *command, int its_cmd)
{
	if (its_cmd)
	{
		command->num_args = command->num_args - 1;
		if (command->num_args == 0)
		{
			free(command->args);
			command->args = NULL;
		}
	}
}

int	ft_check_symbol(t_line_symbol line)
{
	if ((line.symb == '<' && line.flag == 0)
		|| (line.symb == '>' && line.flag == 0)
		|| (line.symb == ';' && line.flag == 0)
		|| (line.symb == '|' && line.flag == 0)
		|| (line.symb == ' ' && line.flag == 0)
		|| (line.symb == '\0'))
		return (0);
	else
		return (1);
}
