#include "../include/minishell.h"

void	del_lst_command(void *cmd)
{
	int	i;

	if (((t_com *)cmd)->args)
	{
		i = 0;
		while (i < ((t_com *)cmd)->num_args)
		{
			free(((t_com *)cmd)->args[i]);
			i++;
		}
		free(((t_com *)cmd)->args);
	}
	if (((t_com *)cmd)->com)
		free(((t_com *)cmd)->com);
	if (((t_com *)cmd)->args_new)
	{
		i = 0;
		while (i < ((t_com *)cmd)->num_args)
		{
			free(((t_com *)cmd)->args_new[i]);
			i++;
		}
		free(((t_com *)cmd)->args_new);
	}
	free((t_com *)cmd);
}

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
    while (MINISHELL_LOOP)
    {
        // тут будут сигналы , добавим позже
        msh->line = NULL; // зануляем каждый раз для новой команды
        success = get_next_line(0, &msh->str);
        if (!success)
            close_prog(msh, "gnl error\n");
        ft_parser(msh);
        ft_command_manage(msh);
		free(msh->line);
		msh->line = NULL;
		ft_lstclear(&msh->com, &del_lst_command);
        free(msh->str);
    }
	return (0);
}