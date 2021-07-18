/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 09:58:34 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 11:21:55 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmp_redir(t_com *command, int *its_cmd, char **tmp, int *args_num)
{
	if (ft_strcmp((*tmp), ">>") && ft_strcmp((*tmp), "<")
		&& ft_strcmp((*tmp), ">") && ft_strcmp((*tmp), "<<"))
	{
		command->com = (*tmp);
		free(command->args[*args_num]);
		*its_cmd = 1;
		return (0);
	}
	return (1);
}

int	ft_get_command(t_com *command)
{
	int				args_num;
	int				its_cmd;
	char			*tmp;
	t_line_symbol	**str;

	its_cmd = 0;
	args_num = 0;
	while (args_num < command->num_args)
	{
		tmp = ft_get_line_from_struct(command->args[args_num], 0,
				ft_mshstrlen(command->args[args_num]));
		if (!ft_cmp_redir(command, &its_cmd, &tmp, &args_num))
			break ;
		free(tmp);
		args_num = args_num + 2;
	}
	if (its_cmd == 1)
		str = malloc(sizeof (t_line_symbol *) * (command->num_args - 1));
	else
		str = malloc(sizeof (t_line_symbol *) * (command->num_args));
	ft_lstadd_front(&g_mem, ft_lstnew(str));
	if (ft_update_line(&str, command, args_num, its_cmd))
		return (1);
	ft_check_if_command(command, its_cmd);
	return (0);
}

int	ft_get_args_num(t_msh *msh, t_com *com, t_list *new_list, int *i)
{
	com->num_args = ft_get_num_of_args(&msh->line[*i]);
	if (com->num_args == 0)
	{
		free(com);
		free(new_list);
		return (0);
	}
	else if (com->num_args > 0)
	{
		com->args = malloc(com->num_args
				* sizeof (t_line_symbol *));
		if (!com->args)
			close_prog("malloc error\n");
		ft_lstadd_front(&g_mem, ft_lstnew(com->args));
	}
	return (1);
}

void	ft_handle_process(t_msh *msh)
{
	t_list	*new_list;
	t_com	*command;
	int		i;
	int		num;

	if (ft_preparser(msh))
		return ;
	i = 0;
	command = NULL;
	while (msh->line[i].symb)
	{
		ft_init_proc(&command, &new_list);
		ft_skip_spaces_in_line(msh, &i);
		ft_get_separator(msh, command, 0, &i);
		ft_skip_spaces_in_line(msh, &i);
		num = ft_get_args_num(msh, command, new_list, &i);
		if (num == 0)
			continue ;
		ft_split_line(msh, command, &i);
		ft_get_separator(msh, command, 1, &i);
		ft_lstadd_back(&msh->com, new_list);
	}
	ft_command_manage(msh);
}
