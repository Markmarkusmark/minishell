#include "../include/minishell.h"

int	ft_redir_checker(t_com *com)
{
	int		i;
	char	*arg;

	i = 0;
	while (i < com->num_args)
	{
		//printf("%c\n", com->args[i]->c);
		arg = ft_struct_to_str(com->args[i], 0, ft_mshstrlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
			 || !ft_strcmp(arg, "<") || !ft_strcmp(arg, "<<"))
			&& com->args[i][0].flag == 0)
		{
			free(arg);
			return (1);
		}
		free(arg);
		i++;
	}
	return (0);
}

void	ft_rdr_count(t_com *com)
{
	int		i;
	char	*arg;

	i = 0;
	com->num_redir = 0;
	while (i < com->num_args)
	{
		arg = ft_struct_to_str(com->args[i], 0, ft_mshstrlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
			 || !ft_strcmp(arg, "<")) && com->args[i][0].flag == 0)
			com->num_redir++;
		free(arg);
		i++;
	}
}

int	ft_mshcmp(t_line_symbol *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i].c || s2[i])
	{
		if (s1[i].c != s2[i])
			return (s1[i].c - s2[i]);
		i++;
	}
	return (0);
}

int 	ft_get_result(t_rdr *rdr, t_com *com, int num, int i)
{
	if (((ft_mshcmp(com->args[num], ">") == 0) || (ft_mshcmp(com->args[num], ">>") == 0)
		 || (ft_mshcmp(com->args[num], "<") == 0)) && com->args[num][0].flag == 0)
	{
		rdr->type = ft_struct_to_str(com->args[num], 0, ft_mshstrlen(com->args[num]));
		if (!rdr->type)
			return (0);
		rdr->file = ft_struct_to_str(com->args[num + 1],
									0, ft_mshstrlen(com->args[num + 1]));
		if (!rdr->file)
			return (0);
		free(com->args[num]);
		free(com->args[num + 1]);
		return (ITS_RDR);
	}
	else
	{
		com->args_new[i] = ft_struct_to_str(com->args[num],
										 0, ft_mshstrlen(com->args[num]));
		if (!com->args_new[i])
			return (0);
		free(com->args[num]);
		return (ITS_ARG);
	}
}

int 	ft_loop(t_rdr *rdr, t_com *com)
{
	int		i;
	int		num;
	int 	rdr_num;
	int 	res;

	i = 0;
	num = 0;
	rdr_num = 0;
	while (num < com->num_args)
	{
		res = ft_get_result(&rdr[rdr_num], com, num, i);
		if (res == 0)
			return (1);
		else if (res == ITS_RDR)
		{
			rdr_num++;
			num = num + 2;
		}
		else if (res == ITS_ARG)
		{
			num++;
			i++;
		}
	}
	return (0);
}

int 	ft_file_check(t_msh *msh, t_rdr rdr, int rdr_num)
{
	int fd;

	fd = 0;
	if (!ft_strcmp(rdr.type, ">"))
	{
		msh->type[1] = rdr_num;
		fd = open(rdr.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (!ft_strcmp(rdr.type, ">>"))
	{
		msh->type[1] = rdr_num;
		fd = open(rdr.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (!ft_strcmp(rdr.type, "<"))
	{
		msh->type[0] = rdr_num;
		fd = open(rdr.file, O_RDONLY);
	}
	else if (!ft_strcmp(rdr.type, "<<"))
	{
		msh->type[0] = rdr_num;
		fd = open(rdr.file, O_RDONLY);
	}
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	ft_not_file_after_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int 	i;
	//char	*sterr;

	i = 0;
	//sterr = strerror(errno);
	while (i < com->num_redir)
	{
		free(rdr[i].type);
		free(rdr[i].file);
		i++;
	}
	free(rdr);
	msh->return_code = 1;
}

void 	ft_launch_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int 	fd[2];
	char	*last_out_file;
	char	*last_in_file;

	fd[0] = NONE; // in
	fd[1] = NONE; // out
	last_in_file = rdr[msh->type[0]].file;
	last_out_file = rdr[msh->type[1]].file;
	if (msh->type[1] != NONE)
	{
		if (!ft_strcmp(rdr[msh->type[1]].type, ">"))
			fd[1] = open(last_out_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else if (!ft_strcmp(rdr[msh->type[1]].type, ">>"))
			fd[1] = open(last_out_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	if (msh->type[0] != NONE)
	{
		if (!ft_strcmp(rdr[msh->type[0]].type, "<"))
			fd[0] = open(last_in_file, O_RDONLY);
		if (!ft_strcmp(rdr[msh->type[0]].type, "<<"))
			fd[0] = open(last_in_file, O_RDONLY);
	}
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
			dup2(fd[0], STDOUT_FILENO);
			close(fd[0]);
		}
		ft_builtin(msh, com);
	}
}

void	ft_execute_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int 	num;
	pid_t	pid;

	pid = fork();
	if (pid == 0) // если дочерний процесс успешно создался
	{
		ft_launch_rdr(msh, rdr, com);
		exit(msh->return_code);
	}
}

void	ft_redir_mng(t_com *com, t_msh *msh)
{
	int		n;
	t_rdr	*rdr;
	int 	delete;
	int 	size;

	msh->return_code = 0;
	ft_rdr_count(com);
	rdr = malloc(com->num_redir * sizeof(t_rdr *));
	if (!rdr)
		close_prog(msh, "malloc error\n");
	msh->type[0] = NONE;
	msh->type[1] = NONE;
	msh->fd_1 = 1; // out
	msh->fd_0 = 0; // in
	delete = com->num_redir * 2;
	size = com->num_args - delete;
	if (size > 0)
	{
		com->args_new = malloc(size * sizeof (char *));
		if (!com->args_new)
			close_prog(msh, "malloc error\n");
	}
	if (ft_loop(rdr, com))
		close_prog(msh, "error\n");
	free(com->args);
	com->args = NULL;
	com->num_args = com->num_args - delete;
	n = 0;
	while (n < com->num_redir)
	{
		if (!ft_file_check(msh, rdr[n], n))
		{
			ft_not_file_after_rdr(msh, rdr, com);
			return;
		}
		n++;
	}
	ft_execute_rdr(msh, rdr, com);
}