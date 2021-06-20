#include "../include/minishell.h"

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
        // после парсера вызываем менеджер команд,передавать будем общую структуру
        free(msh->str);
		free(msh->line);
		msh->line = NULL;
    }
	return (0);
}