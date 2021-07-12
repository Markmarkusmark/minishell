/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 15:36:45 by mryan             #+#    #+#             */
/*   Updated: 2021/07/12 17:45:16 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void env_toarray(t_msh *msh, char **environment)
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
	t_com *com;

	char **environment;
	environment = malloc(255 * ft_lstsize(msh->env));

    com = msh->com->content;
	env_toarray(msh, environment);
	chPID = fork();
	if(chPID == 0) 
	{
		if (execve(path, com->args_new, environment))
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
	t_com 			*com;
	char			**Path;
	DIR				*dir;
	struct dirent	*d; 
	int i = 0;
	char		*path;

    com  = malloc(sizeof(t_com));
    com = msh->com->content;
	Path = get_path();
	//
	
	if (Path)
	{
		while (Path[i++])
		{
			dir = opendir(Path[i]);
			while (dir && (d = readdir(dir)))
			{
				if (ft_strcmp(com->com, d->d_name) == 0)
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
	// else error
	
	return (1);
}