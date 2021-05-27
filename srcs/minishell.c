#include "../include/minishell.h"

char	*get_line(t_all *all)
{
	char	*str;

	str = NULL;
	get_next_line(0, &str);
	return (str);
}

int		ft_check_around(t_all *all, int i)
{
    int j;

    j = 0;
    while (i >= 0 && all->str[i] != ';')
    {
		if (ft_isalnum(all->str[i]))
			j++;
    	if (all->str[i] == '|' && all->str[i + 1] == '|' && j == 0)
            return (0);
        i--;
    }
    if (j == 0)
		return (0);
    else
    	return (1);
}

int		ft_preparse(t_all *all)
{
    int		i;

    i = 0;
    while (all->str[i])
    {
        if ((all->str[i] == ';') && !ft_check_around(all, i - 1))   //--->if (ft_check_around == 0)
            return (0);
        else if (all->str[i] == '|' && all->str[i + 1] != '\0' && all->str[i + 1] == '|')
        {
            if (!ft_check_around(all, i - 1))   //--->if (ft_check_around == 0)
                return (0);
            else
                i++;
        }
        else if ((all->str[i] == '|') && !ft_check_around(all, i - 1))   //--->if (ft_check_around == 0)
            return (0);
        i++;
    }
    return (1);
}

char	**ft_getarr(t_all *all)
{
	char	*tmp;
	int 	flag[3];

	flag[0] = -1;
	flag[1] = 0;
	flag[2] = 0;

}

int 	ft_getcmd(t_all *all)
{
	int i;

	i = 0;
	all->arr1 = ft_getarr(all);
}

int		main(int argc, char **argv, char **env)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		close_prog(all, "error memory");
	ft_bzero(all, sizeof(t_all));
	ft_copyenv(all, env);
	all->str = get_line(all);
	ft_preparse(all);
	if (ft_preparse(all))
		ft_getcmd(all);
	return (0);
}