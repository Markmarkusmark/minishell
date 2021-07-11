#include "../include/minishell.h"

char	**ft_create_argv(t_msh *msh, t_com *com)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc((com->num_args + 2) * sizeof(char *));
	if (!argv)
		close_prog(msh, "error\n");  // тут поменять на ft_exit
	argv[0] = ft_strdup(com->com);
	if (!argv[0])
		close_prog(msh, "error\n");  // тут поменять на ft_exit
	i = 1;
	j = 0;
	while (j < com->num_args)
	{
		argv[i] = ft_strdup(com->args_new[j]);
		if (!argv[i])
			close_prog(msh, "error\n");  // тут поменять на ft_exit
		i++;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}

char	**ft_get_paths(t_msh *msh)
{
	char		**my_paths;
	t_list		*list;

	my_paths = NULL;
	list = msh->env;
	while (list)
	{
		if (!ft_strcmp(((t_env *)list->content)->key, "PATH"))
		{
			if (((t_env *)list->content)->val)
			{
				my_paths = ft_split(((t_env *)list->content)->val, ':');
				if (!my_paths)
					close_prog(msh, "error\n");  // тут поменять на ft_exit
			}
			break ;
		}
		list = list->next;
	}
	return (my_paths);
}

char 	*ft_join_com(t_msh *msh, t_com *com, char *path)
{
	char 	*tmp;
	char 	*tmp2;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		close_prog(msh, "error\n");  // тут поменять на ft_exit
	tmp2 = ft_strjoin(tmp, com->com);
	free(tmp);
	if (!tmp2)
		close_prog(msh, "error\n");  // тут поменять на ft_exit
	else
		return (tmp2);
	free(tmp2);
	return (NULL);
}

int	ft_get_envs_values(t_env *lst, char **env)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(lst->key);
	if (!tmp1)
		return (0);
	*env = ft_strjoin(tmp1, "=");
	if (!*env)
		return (0);
	free(tmp1);
	tmp1 = ft_strdup(*env);
	if (!tmp1)
		return (0);
	free(*env);
	tmp2 = ft_strdup(lst->val);
	if (!tmp2)
		return (0);
	*env = ft_strjoin(tmp1, tmp2);
	if (!*env)
		return (0);
	free(tmp2);
	free(tmp1);
	return (1);
}

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

void 	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int 	ft_exec_com(t_msh *msh, char **argv, char *path)
{
	int 	status;
	char	*err_msg;
	char 	**envs;
	pid_t	pid;

	envs = ft_get_envs(msh);
	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, envs);
		exit(127);
	}
	else if (pid < 0)
	{
		err_msg = strerror(errno);
		close_prog(msh, err_msg);
	}
	waitpid(pid, &status, 0);
	msh->return_code = WEXITSTATUS(status);
	free(path);
	//printf("%d\n", msh->return_code);
	if (msh->return_code)
	{
		free_arr(envs);
		return (1);
	}
	return (0);
}

void 	ft_launch_com(t_msh *msh, t_com *com)
{
	int 	i;
	char 	**exec_paths;
	char 	**argv;
	char 	*buff;
	//char	*err_msg;

	i = 0;
	argv = ft_create_argv(msh, com);
	exec_paths = ft_get_paths(msh);
	while (exec_paths[i])
	{
		buff = ft_join_com(msh, com, exec_paths[i]);
		//printf("%s\n", buff);
		if (buff == NULL)
			close_prog(msh, "command not found\n");
		if (ft_exec_com(msh, argv, buff) == 0)
			break;
		//free(buff);
		//buff = NULL;
		i++;
	}
	if (exec_paths[i] == NULL)
	{
		ft_putstr_fd("command not found in the paths\n", 2);
	}
	free_arr(argv);
	free_arr(exec_paths);
}