#include "../include/minishell.h"

void 	close_prog(t_msh *msh, char *err)
{
    ft_putstr_fd(err, 2);
    free(msh);
    exit(0);
}

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

void    ft_environment(t_msh *msh, char **env)
{
    int		i;
    t_list	*new_lst;
    t_env	*envp;

    i = -1;
    while (env[++i])
    {
        envp = malloc(sizeof(t_env));
        if (!envp)
            close_prog(msh, "error memory");
        new_lst = ft_lstnew(envp);
        if (!new_lst)
            close_prog(msh, "problem with create list");
        msh->env_args = ft_split(env[i], '=');
        if (!msh->env_args)
            close_prog(msh, "str split error");
        envp->key = msh->env_args[0];
        envp->val = msh->env_args[1];
        ft_lstadd_back(&msh->env, new_lst);
        free(msh->env_args);
    }
    ft_clear_oldpwd(msh);
}

int     ft_get_quote_flag(t_msh *msh, const int *i, int q_flag)
{
    if (msh->str[*i] == '\'' && q_flag != 2)
    {
        if (q_flag == 0)
            q_flag = 1;
        else if (q_flag == 1)
            q_flag = 0;
    }
    else if (msh->str[*i] == '"' && q_flag != 1)
    {
        if (q_flag == 0)
            q_flag = 2;
        else if (q_flag == 2)
            q_flag = 0;
    }
    return (q_flag);
}

int 	ft_check_open_quote(int q_flag)
{
	if (q_flag == 1)
	{
		ft_putstr_fd("open single quote\n", 1);
		return (-1);
	}
	if (q_flag == 2)
	{
		ft_putstr_fd("open double quote\n", 1);
		return (-1);
	}
	return (0);
}

int		ft_line_size(t_msh *msh)
{
    int	q_flag;
    int	i;
    int	str_len;
    int err;

    q_flag = 0;
    i = -1;
    str_len = 0;
    while (msh->str[++i])
    {
        q_flag = ft_get_quote_flag(msh, &i, q_flag);
        if (msh->str[i] == '\\' && (!q_flag || (q_flag == 2 && (msh->str[i + 1] == '$'
            || msh->str[i + 1] == '\\' || msh->str[i + 1] == '"'))))
        {
            i++;
            if (msh->str[i] == '\0')
            {
				ft_putstr_fd("open backslash\n", 1);
                return (-1);
            }
        }
        str_len++;
    }
    err = ft_check_open_quote(q_flag);
    if (err != 0)
		return (-1);
    else
		return (str_len);
}

int	ft_get_symbol_flag_utils(t_msh *msh, const int *i, int qte)
{
	if (!qte || (qte == 2 && (msh->str[*i + 1] == '$' || msh->str[*i + 1] == '\\'
		|| msh->str[*i + 1] == '"')))
		return (1);
	return (0);
}

int		ft_get_symbol_flag(t_msh *msh, int *len, int *qte, int *dlr)
{
	if ((msh->str[*len] == '\'' && *qte !=2) || (msh->str[*len] == '"' && *qte != 1))
	{
		*qte = ft_get_quote_flag(msh, len, *qte);
		return (0);
	}
	else if (msh->str[*len] == '\\' && ft_get_symbol_flag_utils(msh, len, *qte))
		return (1);
	else
	{
		if ((*dlr != 0) && (msh->str[*len] != '_') && (ft_isalnum(msh->str[*len]) == 0))
			*dlr = 0;
		else if ((*dlr == 0) && (*qte == 1 || (*qte == 2 && msh->str[*len] != '$'
			&& msh->str[*len] != '\\' && msh->str[*len] != '"')))
			return (1);
		else
		{
			if (msh->str[*len] == '$')
				*dlr = 1;
			return (0);
		}
	}
}

t_line_symbol	*ft_get_struct_line(t_msh *msh, int mlc_len)
{
	int len;
	int chr;
	int qte;
	int dlr;
	t_line_symbol *line;

	len = -1;
	chr = 0;
	qte = 0;
	dlr = 0;
	line = malloc((mlc_len + 1) * sizeof(t_line_symbol));
	if (!line)
		return (NULL);
	while (msh->str[++len])
	{
		line[chr].flag = ft_get_symbol_flag(msh, &len, &qte, &dlr);
		if (msh->str[len] == '\\' && ft_get_symbol_flag_utils(msh, &len, qte))
			len++;
		line[chr].c = msh->str[len];
		chr++;
	}
	line[chr].c = '\0';
	return (line);
}

int					ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	z;

	z = 0;
	while (s1[z] != '\0' || s2[z] != '\0')
	{
		if (s1[z] != s2[z])
			return ((unsigned char)s1[z] - (unsigned char)s2[z]);
		z++;
	}
	return (0);
}

char 	*ft_get_env(t_msh *msh, char *val)
{
	t_list	*list;

	list = msh->env;
	while (list)
	{
		if (!ft_strcmp(val, ((t_env *)list->content)->key))
			return (((t_env *)list->content)->val);
		list = list->next;
	}
	return (NULL);
}

int 	ft_get_val_in_dlr(t_msh *msh, t_line_symbol *line)
{
	int		val_i;
	char 	*val;
	int 	i;
	int 	j;

	i = -1;
	j = 0;
	val_i = 0;
	while (((ft_isalnum(line[val_i].c) == 1) || line[val_i].c == '_')
			&& line[val_i].flag == 0)
		val_i++;
	val = malloc(val_i + 1);
	if (!val)
		return (-1);
	while (++i < val_i)
	{
		val[i] = line[j].c;
		j++;
	}
	val[i] = '\0';
	if (line[0].c == '?')
	{
		msh->val_in_dlr = ft_itoa(msh->return_code); // ноль либо один сюда записывем если встречаем '?'
		val_i++;
		if (!msh->val_in_dlr)
			return (-1);
	}
	else
		msh->val_in_dlr = ft_get_env(msh, val); // или записываем какую переменную окр встретили
	return (val_i);
}

int 	ft_

int		ft_get_dollar(t_msh *msh)
{
	int		begin_str;
	int 	end_str;
	int 	val;

	begin_str = -1;
	end_str = 0;
	val = 0;
	while (msh->line[++begin_str].c)
	{
		if (msh->line[begin_str].c == '$' && msh->line[begin_str].flag == 0)
		{
			begin_str++;
			if (((ft_isalnum(msh->line[begin_str].c) == 0) && msh->line[begin_str].c != '_'
					&& msh->line[begin_str].c != '?') || msh->line[begin_str].flag == 1)
				continue; // вернуться поправить (возможно не нужно будет это условие)
			val = ft_get_val_in_dlr(msh, &msh->line[begin_str]);//тут получаем индекс на котором заканчивается переменная окр и записываем саму переменную в структуру
			if (val == -1) // проверяем записалсь ли переменная окр в структуру
				return (0);
			end_str = begin_str + val;


		}
	}
}

int     ft_preparser(t_msh *msh)
{
    int			str_len;

    str_len = ft_line_size(msh);
	if (str_len == -1)
	{
		msh->return_code = 1; // оригинальный bash возвращает 1 при ошибке
		return (0);
	}
	msh->line = ft_get_struct_line(msh, str_len);
	if (!msh->line)
		close_prog(msh, "line malloc error");
	if (ft_get_dollar(msh) == 0)
		return (0);

    return (1);
}

void     ft_parser(t_msh *msh)
{
    if (ft_preparser(msh) == 0)
		return ;
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
            close_prog(msh, "gnl error");
        ft_parser(msh);
        free(msh->str);
    }
	return (0);
}