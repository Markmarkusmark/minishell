/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 13:11:51 by mryan             #+#    #+#             */
/*   Updated: 2021/07/21 20:54:03 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_file_check(t_msh *msh, t_rdr rdr, int rdr_num)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(rdr.kind, ">"))
	{
		msh->rdr_type[1] = rdr_num;
		fd = open(rdr.arg, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		close(fd);
	}
	else if (!ft_strcmp(rdr.kind, ">>"))
	{
		msh->rdr_type[1] = rdr_num;
		fd = open(rdr.arg, O_WRONLY | O_APPEND | O_CREAT, 0777);
		close(fd);
	}
	else
		ft_file_check_utils(msh, rdr, rdr_num, &fd);
	if (fd == -1)
		return (0);
	return (1);
}

void	ft_not_file_after_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int	i;

	i = 0;
	while (i < com->num_redir)
	{
		free(rdr[i].kind);
		free(rdr[i].arg);
		i++;
	}
	free(rdr);
	msh->return_code = 1;
}

void	ft_launch_rdr_utils_1(t_msh *msh, t_rdr *rdr, char *out)
{
	if (!ft_strcmp(rdr[msh->rdr_type[1]].kind, ">"))
		msh->rdr_fd[1] = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (!ft_strcmp(rdr[msh->rdr_type[1]].kind, ">>"))
		msh->rdr_fd[1] = open(out, O_WRONLY | O_APPEND | O_CREAT, 0777);
}
