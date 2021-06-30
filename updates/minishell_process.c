/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 15:36:45 by mryan             #+#    #+#             */
/*   Updated: 2021/06/30 16:37:51 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main2.c"
#include "dirent.h"
#include <limits.h>
#include <string.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*string;

	if (!s1 || !s2)
		return (ft_strdup(""));
	string = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (*s1)
	{
		string[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		string[i] = *s2;
		i++;
		s2++;
	}
	string[i] = '\0';
	return (string);
}

//
int		main(int argc, char **argv, char **env)
{
	t_msh	*msh;
	int     success;

    if (argc > 1 || argv[1])
        close_prog(msh, "too many arguments\n");
    msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		close_prog(msh, "error memory\n");
	ft_bzero(msh, sizeof(t_msh));
    ft_putstr_fd("this is our fucking shell\n", 1);
    ft_environment(msh, env);
    while (/*MINISHELL_LOOP*/1)
    {
        // тут будут сигналы , добавим позже
        //msh->line = NULL; // зануляем каждый раз для новой команды
        success = get_next_line(0, &msh->str);
        if (!success)
            close_prog(msh, "gnl error\n");
        ft_parser(msh);
        // после парсера вызываем менеджер команд,передавать будем общую структуру
        free(msh->str);
    }
	return (0);
}
//
int			ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	z;

	z = 0;
	while (s1[z] != '\0' || s2[z] != '\0')
	{
		if (s1[z] != s2[z])
			return ((unsigned char)s1[z] - (unsigned char)s2[z]);
		z++;
	}
	return (0);
}


int ft_builtin(t_msh *msh)
{
	t_cmd *cmd;
	cmd  = malloc(sizeof(t_cmd));
	cmd = msh->cmd->content;
	
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		bi_echo(cmd->args_str, 1);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		bi_cd(cmd->args_str, 1);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		bi_pwd(cmd->args_str, 1);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		bi_export(cmd->args_str, &msh, 1);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		bi_unset(cmd->args_str, &msh, 1);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		bi_env(cmd->args_str, &msh, 1);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		bi_exit(cmd->args_str, 1);
	else
		return (0);
	return (1);
}

int list_count(t_list *lst)
{
	t_list *list;
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int env_toarray(t_msh *msh, char **environment)
{
	int i = 0;
	t_list *temp;
	t_env *pair;
	char *str;

	str = (char *)malloc(255 * sizeof(char));
	temp = msh->env;
	while (temp)
	{
		pair = temp->content;
		str = ft_strjoin(pair->key, "=");
		str = ft_strjoin(str, pair->val);
		environment[i] = str;
		temp = temp->next;
		i++;
	}
}

int execute_path(char *path, t_msh *msh)
{
	int chPID;		// Child PID
    int stat;		// Used by parent wait
	t_cmd *cmd;

	char **environment;
	environment = malloc(255 * list_count(msh->env));

	cmd = msh->cmd->content;
	env_toarray(msh, environment);
	chPID = fork();
	if(chPID == 0) 
	{
		if (execve(path, cmd->args_str, msh->env))
			write(1, "executing binary command...\n", 29);
    }
	wait(&stat);
	return (1);
}

char **get_path()
{
	char *pathEnvVar;
	register char *thePath;
	char **path_array;
	char *path;
	int i;

	path_array = (char **)malloc(ARG_MAX);
	i = 0;
	//pathEnvVar = calloc(255, sizeof(char));
	//pathEnvVar = getenv("PATH");
	pathEnvVar = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands";
	if(pathEnvVar)
    	printf("The current path is: %s\n", pathEnvVar);
	
	thePath = (char *)malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath, pathEnvVar);

	path = pathEnvVar;
	if (thePath)
	{
		while (thePath++)
		{
			if (*thePath == ':' || *thePath == '\0') // /?
			{
				path_array[i] = path;
				printf("%s\n", path_array[i]);
				i++;
				if (*thePath == '\0')
					break ;
				*thePath = '\0';
				path = thePath + 1;
			}
		}
	}
	return ((char **)path_array);
}

int ft_binary(t_msh *msh)
{
	t_cmd 			*cmd;
	char			**Path;
	DIR				*dir;
	struct dirent	*d; 
	int i = 0;
	char		*path;

	cmd  = malloc(sizeof(t_cmd));
	cmd = msh->cmd->content;
	Path = get_path();
	//
	
	if (Path)
	{
		while (Path[i++])
		{
			dir = opendir(Path[i]);
			while (dir && (d = readdir(dir)))
			{
				if (ft_strcmp(cmd->cmd, d->d_name) == 0)
				{
					path = Path[i];
					break;
				}
			}
			closedir(dir);
		}
		if (path)
			execute_path(path, msh);
		else
			return (0);
	}
	return (1);
}

int execute_func()
{
	t_msh *msh;
	msh = (t_msh *)malloc(sizeof(t_msh));

	char *arg[] = {
	NULL
	};
	t_cmd cmd;
	cmd.cmd = "export";
	cmd.args_str = arg;
	cmd.n_args = 2;

	t_env ennv;
	ennv.key = "USER";
	ennv.val = "mryan";
	t_env ennv1;
	ennv1.key = "PWD";
	ennv1.val = "/mryan/minishell";
	t_env ennv2;
	ennv2.key = "PATH";
	ennv2.val = "secret";

	msh->cmd = ft_lstnew(&cmd);
	msh->env = ft_lstnew(&ennv);
	ft_lstadd_back(&msh->env, ft_lstnew(&ennv1));
	ft_lstadd_back(&msh->env, ft_lstnew(&ennv2));

	if ((ft_builtin(msh) == 0) || (ft_binary(msh) == 0))
		write(1, "command not found\n", 18);
	ft_bashfunc();
	

}