#include "../include/minishell.h"

void	del_lst_command_utils(void *cmd)
{
	int	i;

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
}

void	del_lst_command(void *cmd)
{
	int	i;

	if (((t_com *)cmd)->com)
		free(((t_com *)cmd)->com);
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
	del_lst_command_utils(cmd);
	free((t_com *)cmd);
}

void	main_init(char **env, t_msh *msh)
{
	ft_bzero(msh, sizeof(t_msh));
	ft_environment(msh, env);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
}

void	main_loop(t_msh *msh)
{
	while (MINISHELL_LOOP)
	{
		//signal(SIGINT, handle_signals);
		msh->line = NULL;
		msh->com = NULL;
		msh->str = readline("minishell> ");
		if (!msh->str)
		{
			ft_putstr_fd("exit", 1);
			break ;
		}
		add_history(msh->str);
		msh->numwaits_pipe = 0;
		msh->pipe_read_fd = 0;
		ft_handle_process(msh);
		ft_lstclear(&msh->com, &del_lst_command);
		free(msh->str);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_msh	*msh;

	msh = NULL;
	if (argc > 1 || argv[1])
		close_prog("too many arguments\n");
	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		close_prog("error memory\n");
	ft_lstadd_front(&g_mem, ft_lstnew(msh));
	main_init(env, msh);
	main_loop(msh);
	return (0);
}
