#include "../include/minishell.h"

void 	ft_echo(t_msh *msh, t_com *com)   // надо добавить опцию -n , пока не придумал реализацию
{
	int	num;

	if (com->args_new == NULL)
	{
		ft_putstr_fd("\n", 1);
		msh->return_code = 0;
		return;
	}
	num = 0;
	while (num < com->num_args)
	{
		ft_putstr_fd(com->args_new[num], 1);
		//ft_putstr_fd("\n", 1);
		if (num < com->num_args - 1)
			ft_putstr_fd(" ", 1);
		num++;
	}
	ft_putstr_fd("\n", 1);
	msh->return_code = 0;
}