/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 13:11:51 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 13:58:37 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_file_check_utils(t_msh *msh, t_rdr rdr, int rdr_num, int *fd)
{
	if (!ft_strcmp(rdr.type, "<"))
	{
		msh->type[0] = rdr_num;
		*fd = open(rdr.file, O_RDONLY);
		close(*fd);
	}
	else if (!ft_strcmp(rdr.type, "<<"))
		msh->type[0] = rdr_num;
}

void	ft_launch_rdr_utils(t_msh *msh, t_com *com, int fd[2])
{
	if (com->com)
	{
		if (fd[1] != NONE)
		{
			dup2(STDOUT_FILENO, msh->fd_1);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (fd[0] != -1)
		{
			dup2(fd[0], msh->fd_0);
			close(fd[0]);
		}
		ft_builtin(msh, com);
	}
}

void	ft_redir_mng_utils(t_com *com, t_msh *msh, int *delete, t_rdr *rdr)
{
	int	n;

	com->args = NULL;
	com->num_args = com->num_args - *delete;
	n = 0;
	while (n < com->num_redir)
	{
		if (!ft_file_check(msh, rdr[n], n))
		{
			ft_not_file_after_rdr(msh, rdr, com);
			return ;
		}
		n++;
	}
	ft_execute_rdr(msh, rdr, com);
}
