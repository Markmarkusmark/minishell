/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 09:52:42 by mryan             #+#    #+#             */
/*   Updated: 2021/07/17 14:11:08 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_file_check(t_msh *msh, t_rdr rdr, int rdr_num)
{
	int	fd;

	fd = 0;
	if (!ft_strcmp(rdr.type, ">"))
	{
		msh->type[1] = rdr_num;
		fd = open(rdr.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		close(fd);
	}
	else if (!ft_strcmp(rdr.type, ">>"))
	{
		msh->type[1] = rdr_num;
		fd = open(rdr.file, O_WRONLY | O_APPEND | O_CREAT, 0777);
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
		free(rdr[i].type);
		free(rdr[i].file);
		i++;
	}
	free(rdr);
	msh->return_code = 1;
}

void	ft_launch_rdr_utils_2(t_msh *msh, t_rdr *rdr,
		char *last_out_file, int fd[2])
{
	if (!ft_strcmp(rdr[msh->type[1]].type, ">"))
		fd[1] = open(last_out_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (!ft_strcmp(rdr[msh->type[1]].type, ">>"))
		fd[1] = open(last_out_file, O_WRONLY | O_APPEND | O_CREAT, 0777);
}

void	ft_launch_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int		fd[2];
	char	*last_out_file;
	char	*last_in_file;
	int		fd_buff[2];
	char	*buff;

	fd[0] = NONE;
	fd[1] = NONE;
	last_in_file = rdr[msh->type[0]].file;
	last_out_file = rdr[msh->type[1]].file;
	if (msh->type[1] != NONE)
		ft_launch_rdr_utils_2(msh, rdr, last_out_file, fd);
	if (msh->type[0] != NONE)
	{
		if (!ft_strcmp(rdr[msh->type[0]].type, "<"))
			fd[0] = open(last_in_file, O_RDONLY);
		if (!ft_strcmp(rdr[msh->type[0]].type, "<<"))
		{
			pipe(fd_buff);
			while (1)
			{
				buff = readline("> ");
				if (!ft_strcmp(rdr[msh->type[0]].file, buff))
				{
					free(buff);
					break ;
				}
				ft_putstr_fd(buff, fd_buff[1]);
				ft_putstr_fd("\n", fd_buff[1]);
				free(buff);
			}
			close(fd_buff[1]);
			fd[0] = fd_buff[0];
		}
	}
	ft_launch_rdr_utils(msh, com, fd);
}

void	ft_execute_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int		num;
	int		status;
	pid_t	pid;

	num = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_launch_rdr(msh, rdr, com);
		exit(msh->return_code);
	}
	if (pid < 0)
		ft_putstr_fd("process crush\n", 2);
	wait(&status);
	msh->return_code = WEXITSTATUS(status);
	while (num < com->num_redir)
	{
		if (rdr[num].type != NULL)
			free(rdr[num].type);
		if (rdr[num].file != NULL)
			free(rdr[num].file);
		num++;
	}
	free(rdr);
}

void	ft_redir_mng(t_com *com, t_msh *msh)
{
	t_rdr	*rdr;
	int		delete;
	int		size;

	msh->return_code = 0;
	ft_rdr_count(com);
	rdr = malloc(com->num_redir * sizeof(t_rdr));
	if (!rdr)
		close_prog("malloc error\n");
	msh->type[0] = NONE;
	msh->type[1] = NONE;
	msh->fd_1 = 1;
	msh->fd_0 = 0;
	delete = com->num_redir * 2;
	size = com->num_args - delete;
	if (size > 0)
	{
		com->args_new = malloc(size * sizeof (char *));
		if (!com->args_new)
			close_prog("malloc error\n");
	}
	if (ft_loop(rdr, com))
		ft_exit(msh, com);
	free(com->args);
	ft_redir_mng_utils(com, msh, &delete, rdr);
}
