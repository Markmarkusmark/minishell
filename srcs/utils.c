/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 18:23:39 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 11:14:08 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_prog(char *err)
{
	ft_putstr_fd(err, 2);
	exit(1);
}

int	ft_mshstrlen(t_line_symbol *line)
{
	int	i;

	i = 0;
	while (line[i].symb)
		i++;
	return (i);
}

t_line_symbol	*ft_mshsubstr(t_msh *msh, size_t len)
{
	size_t			i;
	size_t			j;
	t_line_symbol	*substr;

	i = -1;
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
	while (++i < len)
	{
		substr[j] = msh->line[i];
		j++;
	}
	substr[j].symb = '\0';
	return (substr);
}

t_line_symbol	*ft_mshstrjoin_utils(t_line_symbol *line1,
		t_line_symbol *line2, t_line_symbol	*new_line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line1[j].symb)
	{
		new_line[i] = line1[j];
		i++;
		j++;
	}
	j = 0;
	while (line2[j].symb)
	{
		new_line[i] = line2[j];
		i++;
		j++;
	}
	new_line[i].symb = '\0';
	return (new_line);
}

t_line_symbol	*ft_mshstrjoin(t_line_symbol *line1, t_line_symbol *line2)
{
	t_line_symbol	*new_line;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!line1 || !line2)
		return (NULL);
	new_line = malloc(sizeof (t_line_symbol)
			* (ft_mshstrlen(line1) + ft_mshstrlen(line2) + 1));
	if (!new_line)
		return (NULL);
	return (ft_mshstrjoin_utils(line1, line2, new_line));
}
