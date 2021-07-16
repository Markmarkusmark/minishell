#include "../include/minishell.h"

void	ft_builtin(t_msh *msh, t_com *com)
{
	if (ft_strcmp(com->com, "echo") == 0)
		ft_echo(msh, com);
	else if (ft_strcmp(com->com, "cd") == 0)
		ft_cd(msh, com);
	else if (ft_strcmp(com->com, "pwd") == 0)
		ft_pwd(msh);
	else if (ft_strcmp(com->com, "env") == 0)
		ft_env(msh, com);
	else if (ft_strcmp(com->com, "export") == 0)
		ft_export(msh, com);
	else if (ft_strcmp(com->com, "unset") == 0)
		ft_unset(msh, com);
	else if (ft_strcmp(com->com, "exit") == 0)
		ft_exit(msh, com);
	else
		ft_launch_com(msh, com);
}
