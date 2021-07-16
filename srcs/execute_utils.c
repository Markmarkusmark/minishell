/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 18:11:44 by mryan             #+#    #+#             */
/*   Updated: 2021/07/16 18:14:55 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_create_argv(t_msh *msh, t_com *com)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc((com->num_args + 2) * sizeof(char *));
	if (!argv)
		ft_exit(msh, com);
	argv[0] = ft_strdup(com->com);
	if (!argv[0])
		ft_exit(msh, com);
	i = 1;
	j = 0;
	while (j < com->num_args)
	{
		argv[i] = ft_strdup(com->args_new[j]);
		if (!argv[i])
			ft_exit(msh, com);
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
					ft_exit(msh, msh->com);
			}
			break ;
		}
		list = list->next;
	}
	return (my_paths);
}

char 	*ft_join_com(t_msh *msh, t_com *com, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		ft_exit(msh, com);
	tmp2 = ft_strjoin(tmp, com->com);
	free(tmp);
	if (!tmp2)
		ft_exit(msh, com);
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

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
