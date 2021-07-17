/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:25:49 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 18:16:28 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char 	**ft_get_envs(t_msh *msh)
{
	t_list	*list;
	char	**envs;
	int		i;
	int		j;

	i = ft_lstsize(msh->env);
	envs = malloc((i + 1) * sizeof(char *));
	j = 0;
	list = msh->env;
	while (list)
	{
		if (((t_env *)list->content)->val)
		{
			if (!ft_get_envs_values((t_env *)list->content, &envs[j]))
				return (NULL);
			j++;
		}
		list = list->next;
	}
	envs[j] = NULL;
	return (envs);
}

void	ft_exec_com(t_msh *msh, char **argv, char *path)
{
	int		status;
	char	*err_msg;
	char	**envs;
	pid_t	pid;

	envs = ft_get_envs(msh);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (execve(path, argv, envs) == -1)
		{
			dup2(msh->fd_1, 1);
			err_msg = strerror(errno);
			ft_putstr_fd(err_msg, 2);
			write(1, "\n", 1);
		}
		exit(127);
	}
	else if (pid < 0)
	{
		err_msg = strerror(errno);
		ft_putstr_fd(err_msg, 2);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	msh->return_code = WEXITSTATUS(status);
	if (status == 2)
	{
		ft_putstr_fd("\n", 1);
	}
	if (status == 3)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
	free(path);
	free_arr(envs);
}

char	*ft_its_correct_path(char *path, t_msh *msh, t_com *com)
{
	char		*joined;
	char		*tmp;
	struct stat	stat;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		ft_exit(msh, com);
	joined = ft_strjoin(tmp, com->com);
	if (!joined)
		ft_exit(msh, com);
	free(tmp);
	lstat(joined, &stat);
	if (S_ISREG(stat.st_mode))
		return (joined);
	free(joined);
	return (NULL);
}

void 	ft_launch_com(t_msh *msh, t_com *com)
{
	char	**exec_paths;
	char	**argv;
	int		i;
	char	*buff;

	buff = NULL;
	i = 0;
	argv = ft_create_argv(msh, com);
	exec_paths = ft_get_paths(msh);
	if (exec_paths != NULL)
	{
		i = 0;
		if (com->com[0] == '/')
			buff = ft_strdup(com->com);
		else
		{
			while (exec_paths[i])
			{
				buff = ft_its_correct_path(exec_paths[i], msh, com);
				if (buff)
					break ;
				i++;
			}
			free_arr(exec_paths);
		}
	}
	if (buff == NULL)
	{
		dup2(msh->fd_1, 1);
		ft_putstr_fd("command not found in the paths\n", 2);
		free_arr(argv);
		msh->return_code = 127;
		return ;
	}
	ft_exec_com(msh, argv, buff);
	free_arr(argv);
}
