#include "../include/minishell.h"

int	ft_redir_checker(t_com *com)
{
	int		j;
	char	*str;

	j = 0;
	while (j < com->num_args)
	{
		//printf("%c\n", com->args[i]->c);
		str = ft_get_line_from_struct(com->args[j], 0, ft_mshstrlen(com->args[j]));
		if ((!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
			 || !ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
			&& com->args[j][0].flag == 0)
		{
			free(str);
			return (1);
		}
		free(str);
		j++;
	}
	return (0);
}

void	ft_rdr_count(t_com *com)
{
	int		j;
	char	*str;

	j = 0;
	com->num_redir = 0;
	while (j < com->num_args)
	{
		str = ft_get_line_from_struct(com->args[j], 0, ft_mshstrlen(com->args[j]));
		if ((!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
			 || !ft_strcmp(str, "<") || !ft_strcmp(str, "<<")) &&
			 com->args[j][0].flag == 0)
			com->num_redir++;
		free(str);
		j++;
	}
}

int 	ft_get_result(t_rdr *rdr, t_com *com, int num, int i)
{
	if (((ft_mshcmp(com->args[num], ">") == 0) || (ft_mshcmp(com->args[num], ">>") == 0)
		 || (ft_mshcmp(com->args[num], "<") == 0) || (ft_mshcmp(com->args[num], "<<") == 0)) &&
		 com->args[num][0].flag == 0)
	{
		rdr->type = ft_get_line_from_struct(com->args[num], 0, ft_mshstrlen(com->args[num]));
//		com->com = NULL;
//		rdr->type = ft_struct_to_str2(com, 0, ft_mshstrlen(com->args[num]));
//		printf("%s\n", rdr->type);
		if (!rdr->type)
			return (0);
		rdr->file = ft_get_line_from_struct(com->args[num + 1],
									0, ft_mshstrlen(com->args[num + 1]));
		//printf("%s\n", rdr->file);
		if (!rdr->file)
			return (0);
		free(com->args[num]);
		free(com->args[num + 1]);
//		for (int j = 0; j < 20; j++)
//			printf("%c\n", com->args[j]->c);
		return (ITS_RDR);
	}
	else
	{
//		ft_putstr_fd(com->com, 2);
		com->args_new[i] = ft_get_line_from_struct(com->args[num],
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
    //printf("%d\n", com->num_args);
	while (num < com->num_args)
	{
		res = ft_get_result(&rdr[rdr_num], com, num, i);
//		ft_putstr_fd(com->com, 2);
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
		close(fd);
	}
	else if (!ft_strcmp(rdr.type, ">>"))
	{
		msh->type[1] = rdr_num;
		fd = open(rdr.file, O_WRONLY | O_APPEND | O_CREAT, 0777);
		close(fd);
	}
	else if (!ft_strcmp(rdr.type, "<"))
	{
		msh->type[0] = rdr_num;
		fd = open(rdr.file, O_RDONLY);
		close(fd);
	}
	else if (!ft_strcmp(rdr.type, "<<"))
	{
		msh->type[0] = rdr_num;
		//fd = open(rdr.file, O_RDONLY);
	}
	if (fd == -1)
		return (0);
	return (1);
}

void	ft_not_file_after_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int 	i;

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
		if (!ft_strcmp(rdr[msh->type[1]].type, ">")) {
			fd[1] = open(last_out_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		}
		else if (!ft_strcmp(rdr[msh->type[1]].type, ">>")) {
			fd[1] = open(last_out_file, O_WRONLY | O_APPEND | O_CREAT, 0777);
		}
	}
	if (msh->type[0] != NONE)
	{
		if (!ft_strcmp(rdr[msh->type[0]].type, "<")) {
			fd[0] = open(last_in_file, O_RDONLY);
			//printf("%d\n", fd[0]);
		}
		if (!ft_strcmp(rdr[msh->type[0]].type, "<<"))
		{
			//printf("%s\n", rdr[msh->type[0]].file);
			int	fd_buff[2];
			char *buff;

			pipe(fd_buff);
			while (1)
			{
				//printf("%d\n", fd_buff[0]);
				//printf("%d\n", fd_buff[1]);
				buff = readline("> ");
				//printf("%s\n", buff);
				//get_next_line(0, &buff);
				if (!ft_strcmp(rdr[msh->type[0]].file, buff))
				{
					free(buff);
					break;
				}
				ft_putstr_fd(buff, fd_buff[1]);
				ft_putstr_fd("\n", fd_buff[1]);
				free(buff);
				//fd[0] = open(last_in_file, O_RDONLY);
			}
			close(fd_buff[1]);
			fd[0] = fd_buff[0];
		}
	}
//	ft_putstr_fd(com->com, 2);
	if (com->com)
	{

		if (fd[1] != NONE)
		{
			dup2(STDOUT_FILENO, msh->fd_1);
			dup2(fd[1], STDOUT_FILENO);
//			printf("%d\n", fd[1]);
			//dup2(fd[1], msh->fd_1);
			close(fd[1]);
		}
		if (fd[0] != -1)
		{
			//printf("cwecwcw\n");
			dup2(fd[0], msh->fd_0);
			close(fd[0]);
		}
//		sleep(100);
		ft_builtin(msh, com);
	}
}

void	ft_execute_rdr(t_msh *msh, t_rdr *rdr, t_com *com)
{
	int 	num;
	int 	status;
	pid_t	pid;
	char 	*err_msg;

	num = 0;
	//printf("%s\n", com->com);
	//ft_putstr_fd(com->com, 2);
	pid = fork();
	if (pid == 0) // если дочерний процесс успешно создался
	{
//		ft_putstr_fd(com->com, 2);
		ft_launch_rdr(msh, rdr, com);
		exit(msh->return_code);
	}
	if (pid < 0)
	{
		err_msg = strerror(errno);
		ft_putstr_fd(err_msg, 2);
	}
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
	int		n;
	t_rdr	*rdr;
	int 	delete;
	int 	size;

//	ft_putstr_fd(com->com, 2);
	msh->return_code = 0;
	ft_rdr_count(com);
	rdr = malloc(com->num_redir * sizeof(t_rdr));
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
//	ft_putstr_fd(com->com, 2);
	if (ft_loop(rdr, com))
		close_prog(msh, "error\n");
//    if (!cleaner_loop(com, rdr))
//        close_prog(msh, "error\n");
	//ft_putstr_fd(com->com, 2);
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