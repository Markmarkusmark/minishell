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

int     ft_get_quote_flag(t_msh *msh, int *i)
{
    int q_flag;

    q_flag = 0;
    if (msh->str[*i] == '\'' && q_flag != 2)
    {
        if (!q_flag)
            q_flag = 1;
        else if (q_flag == 1)
            q_flag = 0;
    }
    else if (msh->str[*i] == '"' && q_flag != 1)
    {
        if (!q_flag)
            q_flag = 2;
        else if (q_flag == 2)
            q_flag = 0;
    }
    return (q_flag);
}

int	esc_size(t_msh *msh)
{
    int	q_flag;
    int	i;
    int	j;

    q_flag = 0;
    i = -1;
    j = 0;
    while (msh->str[++i])
    {
        q_flag = ft_get_quote_flag(msh, &i);
        if (msh->str[i] == '\\' && (!q_flag || (q_flag == 2 && (msh->str[i + 1] == '$'
            || msh->str[i + 1] == '\\' || msh->str[i + 1] == '"'))))
        {
            i++;
            if (msh->str[i] == '\0')
            {
                write(2, "open backslash\n", 23);
                return (-1);
            }
        }
        j++;
    }
    return (open_quote_checks(q_flag, j));
}

int     ft_preparser(t_msh *msh)
{
    int			len;

    len = esc_size(msh);
    if (len == -1)
    {
        data->ret = 1;
        return (0);
    }
    data->line = line_to_struct(str, len);
    if (!data->line)
        ft_exit(data, NULL);
    if (!dollar_finder(&data->env_head, &data->line, data->ret))
        return (0);
    if (!syntax_errors(data->line))
    {
        free(data->line);
        data->ret = 258;
        return (0);
    }
    return (1);
}

int     ft_parser(t_msh *msh)
{
    if (!(ft_preparser(msh)))
        close_prog(msh, "string syntax error");

    return (1);
}

int		main(int argc, char **argv, char **env)
{
	t_msh	*msh;
	int     success;

    if (argc > 1 || argv[1])
        close_prog(msh, "too many arguments");
    msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		close_prog(msh, "error memory");
	ft_bzero(msh, sizeof(t_msh));
    ft_putstr_fd("this is our fucking shell", 1);
    ft_environment(msh, env);
    while (MINISHELL_LOOP)
    {
        //here will be signals
        success = get_next_line(0, &msh->str);
        if (!success)
            close_prog(msh, "gnl error");
        ft_parser(msh);
    }
	return (0);
}