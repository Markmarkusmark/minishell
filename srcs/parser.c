#include "../include/minishell.h"

void 	ft_get_separator(t_msh *msh, t_com *command, int separ, int *i)
{
	if (separ == 1)
	{
		if ((msh->line[*i].c == ';' || msh->line[*i].c == '|')
				&& msh->line[*i].flag == 0)
			command->separ2 = msh->line[*i].c;
	}
	if (separ == 0)
	{
		if ((msh->line[*i].c == ';' || msh->line[*i].c == '|')
			&& msh->line[*i].flag == 0)
		{
			command->separ = msh->line[*i].c;
			*i++;
		}
	}
}

void     ft_parser(t_msh *msh)
{
    t_list  *new_list;
    t_com   *command;
    int     i;

	if (ft_preparser(msh) == 1)
		return ;
	i = 0;
	while (msh->line[i].c)
    {
	    command = malloc(sizeof (t_com));
        if (!command)
            close_prog(msh, "malloc error\n");
        new_list = ft_lstnew(command);
        if (!new_list)
            close_prog(msh, "malloc error\n");
        ft_bzero(command, sizeof (t_com)); // проверить через дебаггер зануляет ли
        while (msh->line[i].c == ' ' && msh->line[i].flag == 0)
            i++;
		ft_get_separator(msh, command, 0, &i);
		while (msh->line[i].c == ' ' && msh->line[i].flag == 0)
			i++;

    }
}