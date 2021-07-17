/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 10:11:36 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 10:12:25 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

// void	ft_get_num_of_args_utils(t_line_symbol *line, int *i, int *num_args)
// {
// 	if ((line[*i].symb == '>' || line[*i].symb == '<') && line[*i].flag == 0)
// 	{
// 		*num_args++;
// 		while ((line[*i].symb == '>' || line[*i].symb == '<')
// 			&& line[*i].flag == 0)
// 			(*i)++;
// 	}
// }

int	ft_get_num_of_args(t_line_symbol *line)
{
	int	i;
	int	num_args;

	i = 0;
	num_args = 0;
	while (line[i].symb)
	{
		if ((line[i].symb == ';' || line[i].symb == '|') && line[i].flag == 0)
			break ;
		if ((line[i].symb == '>' || line[i].symb == '<') && line[i].flag == 0)
		{
			num_args++;
			while ((line[i].symb == '>' || line[i].symb == '<')
				&& line[i].flag == 0)
				i++;
		}
		//ft_get_num_of_args_utils(line, &i, &num_args);
		else
		{
			while (ft_check_symbol(line[i]))
				i++;
			num_args++;
		}
		while (line[i].symb == ' ' && line[i].flag == 0)
			i++;
	}
	return (num_args);
}

t_line_symbol	*ft_get_clean_line(t_line_symbol *line)
{
	int				i;
	int				j;
	t_line_symbol	*new_line;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	new_line = malloc((ft_mshstrlen(line) + 1) * sizeof (t_line_symbol));
	if (!new_line)
		return (NULL);
	while (line[i].symb)
	{
		if (!(line[i].flag == 0
				&& (line[i].symb == '"' || line[i].symb == '\'')))
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j].symb = '\0';
	return (new_line);
}

int	ft_pass_str(int *i, t_msh *msh)
{
	int	j;

	j = *i;
	if (msh->line[*i].flag == 0
		&& (msh->line[*i].symb == '>' || msh->line[*i].symb == '<'))
	{
		while (msh->line[j].flag == 0
			&& (msh->line[j].symb == '>' || msh->line[j].symb == '<'))
			j++;
	}
	else
	{
		while (ft_check_token3(msh, &j))
			j++;
	}
	return (j);
}

t_line_symbol	*ft_mshsubstr2(t_msh *msh, int n, size_t len)
{
	size_t			i;
	size_t			j;
	t_line_symbol	*substr;

	i = n;
	j = 0;
	if (!msh->line)
		return (NULL);
	substr = malloc(sizeof (t_line_symbol) * (len + 1));
	if (!substr)
		return (NULL);
	if (msh->line[0].symb == '\0')
	{
		substr[0].symb = '\0';
		substr[0].flag = 0;
		return (substr);
	}
	while (i < (len + n))
	{
		substr[j] = msh->line[i];
		i++;
		j++;
	}
	substr[j].symb = '\0';
	return (substr);
}
