/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:11:15 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 11:20:26 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_line_from_struct(t_line_symbol *line, int beg, int size)
{
	int		i;
	int		j;
	char	*new_line;

	if (!line)
		return (NULL);
	if (line[0].symb == '\0')
		return (ft_strdup(""));
	if (beg > ft_mshstrlen(line))
		return (ft_strdup(""));
	new_line = malloc(size + 1);
	if (!new_line)
		return (NULL);
	i = beg;
	j = 0;
	while (i < (size + beg))
	{
		new_line[j] = line[i].symb;
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

int	ft_args_new(t_com *com)
{
	int	i;

	if (com->num_args > 0)
	{
		com->args_new = calloc(com->num_args, sizeof(char *));
		if (!com->args_new)
			return (0);
	}
	i = 0;
	while (i < com->num_args)
	{
		com->args_new[i] = ft_get_line_from_struct(com->args[i], 0,
				ft_mshstrlen(com->args[i]));
		free(com->args[i]);
		com->args[i] = NULL;
		i++;
	}
	if (com->num_args > 0)
		com->args_new[i] = NULL;
	free(com->args);
	com->args = NULL;
	return (1);
}

void	ft_exec_all(t_msh *msh, t_com *com)
{
	if (ft_redir_checker(com))
		ft_redir_mng(com, msh);
	else
	{
		if (!ft_args_new(com))
			close_prog("error memory\n");
		ft_builtin(msh, com);
	}
}

void	ft_lauch_pipe(t_msh *msh, t_com *com, pid_t *pidpipe)
{
	if (com->pipe_in == '|')
	{
		ft_pipe_out(msh, com);
		msh->numwaits_pipe++;
		if (msh->pipe_read_fd)
			close(msh->pipe_read_fd);
		msh->pipe_read_fd = msh->pipe_fd[0];
		close(msh->pipe_fd[1]);
	}
	else if (com->pipe_out == '|')
	{
		ft_pipe_in(msh, com, pidpipe);
		close(msh->pipe_read_fd);
		msh->pipe_read_fd = 0;
	}
}

void	ft_command_manage(t_msh *msh)
{
	t_list	*list;
	pid_t	pidpipe;

	list = msh->com;
	while (list)
	{
		pidpipe = 0;
		if (((t_com *)list->content)->pipe_out != '|'
			&& ((t_com *)list->content)->pipe_in != '|')
			ft_exec_all(msh, (t_com *)list->content);
		ft_lauch_pipe(msh, (t_com *)list->content, &pidpipe);
		ft_check_wait(msh, (t_com *)list->content, &pidpipe);
		list = list->next;
	}
	free(msh->line);
	msh->line = NULL;
}
