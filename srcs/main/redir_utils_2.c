/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 13:11:51 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 13:34:51 by mryan            ###   ########.fr       */
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
