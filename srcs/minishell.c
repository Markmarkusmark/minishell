#include "../include/minishell.h"

void	del_lst_command(void *cmd)
{
	int	i;

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
		if (((t_com *)cmd)->args_new != NULL)
			free(((t_com *)cmd)->args_new);
	}
	free((t_com *)cmd);
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
}

int		main(int argc, char **argv, char **env)
{
	t_msh	*msh;
	char	*str;
	//int     success;

	msh = NULL; //
    if (argc > 1 || argv[1])
        close_prog(msh, "too many arguments\n");
    msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		close_prog(msh, "error memory\n");
	ft_bzero(msh, sizeof(t_msh));
    ft_putstr_fd("this is our fucking shell\n", 1);
    ft_environment(msh, env);

	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    
	while (MINISHELL_LOOP)
    {
        // тут будут сигналы , добавим позже
        msh->line = NULL; // зануляем каждый раз для новой команды
        msh->com = NULL;
//		ft_putstr_fd(MAGENTA"a", 1);
//		ft_putstr_fd(RED"s", 1);
//		ft_putstr_fd(GREEN"h", 1);
//		ft_putstr_fd(BLUE"a", 1);
//		ft_putstr_fd(YELLOW"l", 1);
//		ft_putstr_fd(CYAN"e", 1);
//		ft_putstr_fd(MAGENTA"t", 1);
//		ft_putstr_fd(YELLOW"> "RESET, 1);
//        success = get_next_line(0, &msh->str);
		str = readline("custom_shell> ");
		if (str != NULL)
			msh->str = str;
		else
			break;
//        if (!success)
//            close_prog(msh, "gnl error\n");
        ft_parser(msh);
        ft_command_manage(msh);
		free(msh->line);
		msh->line = NULL;
		ft_lstclear(&msh->com, &del_lst_command);
        free(msh->str);
    }
	return (0);
}