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

int 	ft_pass_str(int *i, t_msh *msh)
{
	int	j;

	j = *i;
	if (msh->line[*i].flag == 0 && (msh->line[*i].c == '>' ||
		msh->line[*i].c == '<'))
	{
		while (msh->line[*i].flag == 0 && (msh->line[*i].c == '>' ||
			msh->line[*i].c == '<'))
			j++;
	}
	else
	{
		while (ft_check_token3(msh, &j))
			j++;
	}
	return (j);
}

t_line_symbol 	*ft_mshsubstr2(t_msh *msh, int n, size_t len)
{
	size_t			i;
	size_t			j;
	t_line_symbol	*substr;

	i = n;
	j = 0;
	if (!msh->line)
		return (NULL);
	substr = malloc(sizeof (t_line_symbol) * (len + 1));
	if (!substr)
		return (NULL);
	if (msh->line[0].c == '\0')
	{
		substr[0].c = '\0';
		substr[0].flag = 0;
		return (substr);
	}
	while (i < (len + n))
	{
		substr[j] = msh->line[i];
		i++;
		j++;
	}
	substr[j].c = '\0';
	return (substr);
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
		j = ft_pass_str(i, msh);
		cmd->args[num] = ft_mshsubstr2(msh, *i, j - *i);
		if (!cmd->args[num])
			return (1);
		while (msh->line[*i].c == ' ' && msh->line[*i].flag == 0)
			*i = *i + 1;
		num++;
	}
	return (0); // если успешно завершится
}

char	*ft_get_str_from_struct(t_line_symbol *line, int len)
{
	int 	i;
	int 	j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[j] = line[i].c;
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

t_line_symbol	*ft_mshdup(t_line_symbol *line)
{
	int				i;
	int 			len;
	t_line_symbol	*dup_line;

	len = ft_mshstrlen(line);
	if (!line)
		return (NULL);
	dup_line = malloc((len + 1) * sizeof(t_line_symbol *));
	if (!dup_line)
		return (NULL);
	i = 0;
	while (line[i].c)
	{
		dup_line[i] = line[i];
		i++;
	}
	dup_line[i].c = '\0';
	return (dup_line);
}

int		ft_update_line(t_line_symbol ***str, t_com *cmd, int num, int its_cmd)
{
	int	n;
	int i;

	n = 0;
	i = 0;
	while (n <cmd->num_args)
	{
		if (n == num && its_cmd == 1)
		{
			n++;
			continue;
		}
		(*str)[i] = ft_mshdup(cmd->args[n]);
		if (!(*str)[i])
			return (1);
		free(cmd->args[n]);
		i++;
		n++;
	}
	free(cmd->args);
	cmd->args = *str;
	return (0);
}

int 	ft_get_command(t_com *command)
{
	int				args_num;
	int 			its_cmd;
	int 			tmp_len;
	char 			*tmp;
	t_line_symbol	**str;

	its_cmd = 0;
	args_num = 0;
	while (args_num < command->num_args)
	{
		tmp = ft_get_str_from_struct(command->args[args_num],
									 ft_mshstrlen(command->args[args_num]));
		if (!tmp)
			return (1);
		if (ft_strcmp(tmp, ">>") && ft_strcmp(tmp, "<") && ft_strcmp(tmp, ">"))
		{
			command->com = tmp;
			free(command->args[args_num]);
			its_cmd = 1;
			break;
		}
		free(tmp);
		args_num = args_num + 2;
	}
	if (its_cmd == 1)
		str = malloc(sizeof (t_line_symbol *) * (command->num_args - 1));
	else
		str = malloc(sizeof (t_line_symbol *) * (command->num_args));
	if (!str)
		return (1);
	if (ft_update_line(&str, command, args_num, its_cmd))
		return (1);
	if (its_cmd == 1)
	{
		command->num_args = command->num_args - 1;
		if (command->num_args == 0)
		{
			free(command->args);
			command->args = NULL;
		}
	}
	return (0);
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
        if (ft_get_command(command))
			close_prog(msh, "command not found\n");
    }
}