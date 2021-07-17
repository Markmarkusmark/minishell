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

void	ft_rdr_init(t_msh *msh, t_rdr *rdr, char **in, char **out)
{
	msh->rdr_fd[0] = NONE;
	msh->rdr_fd[1] = NONE;
	(*in) = rdr[msh->rdr_type[0]].arg;
	(*out) = rdr[msh->rdr_type[1]].arg;
}

void	ft_launch_rdr_utils_0(t_msh *msh, t_rdr *rdr, char *in)
{
	char	*buff;

	if (!ft_strcmp(rdr[msh->rdr_type[0]].kind, "<"))
		msh->rdr_fd[0] = open(in, O_RDONLY);
	if (!ft_strcmp(rdr[msh->rdr_type[0]].kind, "<<"))
	{
		pipe(msh->rdr_fd2);
		while (1)
		{
			buff = readline("> ");
			if (!ft_strcmp(rdr[msh->rdr_type[0]].arg, buff))
			{
				free(buff);
				break ;
			}
			ft_putstr_fd(buff, msh->rdr_fd2[1]);
			ft_putstr_fd("\n", msh->rdr_fd2[1]);
			free(buff);
		}
		close(msh->rdr_fd2[1]);
		msh->rdr_fd[0] = msh->rdr_fd2[0];
	}
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
	char	*out;
	char	*in;

<<<<<<< HEAD
	ft_rdr_init(msh, rdr, &in, &out);
	if (msh->rdr_type[1] != NONE)
		ft_launch_rdr_utils_1(msh, rdr, out);
	if (msh->rdr_type[0] != NONE)
		ft_launch_rdr_utils_0(msh, rdr, in);
	if (com->com)
	{
		if (msh->rdr_fd[1] != NONE)
=======
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
>>>>>>> 93ab37c313bba67daacd4cb9cddbca3eef0fddc3
		{
			dup2(STDOUT_FILENO, msh->fd_1);
			dup2(msh->rdr_fd[1], STDOUT_FILENO);
			close(msh->rdr_fd[1]);
		}
		if (msh->rdr_fd[0] != -1)
		{
			dup2(msh->rdr_fd[0], msh->fd_0);
			close(msh->rdr_fd[0]);
		}
		ft_builtin(msh, com);
	}
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
		if (rdr[num].kind != NULL)
			free(rdr[num].kind);
		if (rdr[num].arg != NULL)
			free(rdr[num].arg);
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
	msh->rdr_type[0] = NONE;
	msh->rdr_type[1] = NONE;
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
