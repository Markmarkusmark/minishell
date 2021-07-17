/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 09:55:31 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 09:58:14 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe_out(t_msh *msh, t_com *com)
{
	pid_t	pid;
	char	*err_msg;

	pipe(msh->pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		if (msh->pipe_read_fd)
		{
			dup2(msh->pipe_read_fd, 0);
			close(msh->pipe_read_fd);
		}
		close(msh->pipe_fd[0]);
		dup2(msh->pipe_fd[1], 1);
		close(msh->pipe_fd[1]);
		ft_exec_all(msh, com);
		exit(msh->return_code);
	}
	else if (pid < 0)
	{
		err_msg = strerror(errno);
		ft_putstr_fd(err_msg, 2);
	}
}

void	ft_check_wait(t_msh *msh, t_com *com, pid_t *pidpipe)
{
	int	status;
	int	i;

	i = 0;
	if ((com->pipe_in == '-' || com->pipe_in == ';') && *pidpipe != 0)
	{
		waitpid(*pidpipe, &status, 0);
		msh->return_code = WEXITSTATUS(status);
		while (i < msh->numwaits_pipe - 1)
		{
			wait(NULL);
			i++;
		}
		msh->numwaits_pipe = 0;
	}
}

void	ft_pipe_in(t_msh *msh, t_com *com, pid_t *pidpipe)
{
	pid_t	pid;
	char	*err_msg;

	pid = fork();
	if (pid == 0)
	{
		dup2(msh->pipe_read_fd, 0);
		close(msh->pipe_read_fd);
		ft_exec_all(msh, com);
		exit(msh->return_code);
	}
	else if (pid < 0)
	{
		err_msg = strerror(errno);
		ft_putstr_fd(err_msg, 2);
	}
	msh->numwaits_pipe++;
	*pidpipe = pid;
}
