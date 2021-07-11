#include "../include/minishell.h"

char	*ft_struct_to_str(t_line_symbol *struc, int start, int len)
{
    int		i;
    int		j;
    char	*str;

    if (!struc)
        return (NULL);
	if (struc[0].c == '\0')
		return (ft_strdup(""));
	if (start > ft_mshstrlen(struc))
		return (ft_strdup(""));
    str = malloc(len + 1);
    if (!str)
        return (NULL);
    i = start;
    j = 0;
    while (i < (len + start))
    {
        str[j] = struc[i].c;
        i++;
        j++;
    }
    str[j] = '\0';
    return (str);
}

int	ft_args_new(t_com *com)
{
    int	i;

    if (com->num_args > 0)
    {
        com->args_new = calloc(com->num_args, sizeof(char *));
        if (!com->args_new)
            return (0);
    }
    i = 0;
    while (i < com->num_args)
    {
        com->args_new[i] = ft_struct_to_str(com->args[i], 0, ft_mshstrlen(com->args[i]));
        free(com->args[i]);
		com->args[i] = NULL;
        i++;
    }
    if (com->num_args > 0)
    	com->args_new[i] = NULL;
    free(com->args);
    com->args = NULL;
    return (1);
}

void	ft_command_manage(t_msh *msh)
{
    t_list	*list;

    list = msh->com;
    msh->read_fd = 0;
	//printf("eerferf\n");
    while (list)
    {
        if (((t_com *)list->content)->pipe_out != '|'
            && ((t_com *)list->content)->pipe_in != '|')
        {
            if (ft_redir_checker((t_com *)list->content))
                ft_redir_mng((t_com *)list->content, msh);
            else
            {
                if (!ft_args_new((t_com *)list->content))
                    close_prog(msh, "error memory\n");
//                for (int i = 0; i < 7; i++)
//                {
//                    printf("%c", ((t_com *)list->content)->args_new[0][i]);
//                }
//                printf("\n");
//                for (int j = 0; j < 7; j++)
//                {
//                    printf("%c", ((t_com *)list->content)->args_new[1][j]);
//                }
//                printf("\n");
//                printf("%d\n", ((t_com *)list->content)->num_args);
//                ft_builtin((t_com *)list->content, msh);
//                if ((ft_builtin(msh, (t_com *)list->content) == 0))  /* || (ft_binary(msh) == 0)*/
//                    close_prog(msh, "command not found\n");
				//printf("тут аргумент : %s\n", ((t_com *)list->content)->args_new[0]);
				ft_builtin(msh, (t_com *)list->content);
            }
        }
//        else if (((t_cmd *)lst->content)->sep_0 == '|')
//            ft_handle_pipe_input(msh, (t_com *)list->content);
//        if (((t_cmd *)lst->content)->sep_1 == '|')
//        {
//            pipe(fd);
//            ft_handle_pipe_output(msh, (t_com *)list->content);
//        }
        list = list->next;
    }
}