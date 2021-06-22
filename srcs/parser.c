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

void    ft_skip_spaces(t_msh *msh, int *i)
{
    while (msh->line[*i].c == ' ' && msh->line[*i].flag == 0)
        *i++;
}

int     ft_check_symbol(t_line_symbol line)
{
    if ((line.c == '<' && line.flag == 0) ||
        (line.c == '>' && line.flag == 0) ||
        (line.c == ';' && line.flag == 0) ||
        (line.c == '|' && line.flag == 0) ||
        (line.c == ' ' && line.flag == 0) ||
        (line.c == '\0'))
        return (0);
    else
        return (1);
}

int     ft_get_num_of_args(t_line_symbol *line)
{
    int	i;
    int	num_args;

    i = 0;
    num_args = 0;
    while (line[i].c)
    {
        if ((line[i].c == ';' || line[i].c == '|') && line[i].flag == 0)
            break ;
        if ((line[i].c == '>' || line[i].c == '<') && line[i].flag == 0)
        {
            num_args++;
            while ((line[i].c == '>' || line[i].c == '<') && line[i].flag == 0)
                i++;
        }
        else
        {
            while (ft_check_symbol(line[i]))
                i++;
            num_args++;
        }
        while (line[i].c == ' ' && line[i].flag == 0)
            i++;
    }
    return (num_args);
}

t_line_symbol	*ft_get_clean_line(t_line_symbol *line)
{
	int 			i;
	int 			j;
	t_line_symbol	*new_line;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	new_line = malloc((ft_mshstrlen(line) + 1) * sizeof (t_line_symbol));
	if (!new_line)
		return (NULL);
	while (line[i].c)
	{
		if (!(line[i].flag == 0 && (line[i].c == '"' || line[i].c == '\'')))
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j].c = '\0';
	return (new_line);
}

int 	ft_get_args(t_msh *msh, t_com *cmd, int *i)
{
	int 			j;
	int 			num;
	t_line_symbol	*line2;

	num = 0;
	line2 = ft_get_clean_line(msh->line);
	if (line2 == NULL)
		return (1);
	free(msh->line);
	msh->line = line2;
	while (msh->line[*i].c == ' ' && msh->line[*i].flag == 0)
		*i = *i + 1;
	while (num < cmd->num_args)
	{

	}
	return (0); // если успешно завершится
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
        ft_skip_spaces(msh, &i);
		ft_get_separator(msh, command, 0, &i);
        ft_skip_spaces(msh, &i);
        command->num_args = ft_get_num_of_args(&msh->line[i]);
        if (command->num_args == 0)
		{
        	free(command);
        	free(new_list);
			continue ;
		}
        else if (command->num_args > 0)
		{
			command->args = malloc(command->num_args * sizeof (t_line_symbol *));
			if (!command->args)
				close_prog(msh, "malloc error\n");
		}
        if (ft_get_args(msh, command, &i))
			close_prog(msh, "arguments error\n");
    }
}