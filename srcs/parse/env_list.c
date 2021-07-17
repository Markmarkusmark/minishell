#include "../include/minishell.h"

void	ft_clear_oldpwd(t_msh *msh)
{
	t_list	*list;

	list = msh->env;
	while (list)
	{
		if (!ft_strncmp(((t_env *)list->content)->key, "OLDPWD", 6))
		{
			free(((t_env *)list->content)->val);
			((t_env *)list->content)->val = NULL;
			return ;
		}
		list = list->next;
	}
}

void	ft_environment(t_msh *msh, char **env)
{
	int		i;
	t_list	*new_lst;
	t_env	*envp;

	i = -1;
	while (env[++i])
	{
		envp = malloc(sizeof(t_env));
		if (!envp)
			close_prog("error memory\n");
		new_lst = ft_lstnew(envp);
		if (!new_lst)
			close_prog("problem with create list\n");
		msh->env_args = ft_split(env[i], '=');
		if (!msh->env_args)
			close_prog("str split error\n");
		envp->key = msh->env_args[0];
		envp->val = msh->env_args[1];
		ft_lstadd_back(&msh->env, new_lst);
		free(msh->env_args);
	}
	ft_clear_oldpwd(msh);
}
