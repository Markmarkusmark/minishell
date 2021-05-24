#include "../include/minishell.h"

void 	close_prog(t_all *all, char *err)
{
	ft_putstr_fd(err, 2);
	free(all);
	exit(0);
}

char 	*ft_quote(t_all *all, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (all->str[++(*i)])
		if (all->str[*i] == '\'')
			break ;
	tmp = ft_substr(all->str, 0, j);
	tmp2 = ft_substr(all->str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(all->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp = %s\n", tmp);
	free(all->str);
	return (tmp);
}

char 	*ft_double_quote(t_all *all, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (all->str[++(*i)])
	{
		if (all->str[*i] == '\\' && (all->str[*i + 1] == '\"' || all->str[*i + 1] == '\'' ||
		all->str[*i + 1] == '\\' || all->str[*i + 1] == '\"'))
			str = ft_backslash(str, i);
		if (all->str[*i] == '\"')
			break;
	}
	tmp = ft_substr(all->str, 0, j);
	tmp2 = ft_substr(all->str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(all->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp = %s\n", tmp);
	free(all->str);
	return (tmp);
}

char 	*ft_backslash(t_all *all, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(all->str, 0, *i);
	tmp2 = ft_strdup(all->str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(all->str);
	++(*i);
	printf("tmp = %s\n", tmp);
	return (tmp);
}

void 	ft_parser(t_all *all)
{
	//	"", '', \, $, ;, |, <, >, <<
	//	все что в "" остается без изменений, кроме $ и \
	//	все что в '' остается без изменений
	//	\ обрабатывает след символ после себя
	//	$ распаршивает окружение и вытаскивает переменную
	//	; делит команды
	//	| перенаправляет
	int	i;

	i = -1;
	while (all->str[++i])
	{
		if (all->str[i] == '\'')
			all->str = ft_quote(all, &i);
		if (all->str[i] == '\\')
			all->str = ft_backslash(all, &i);
		if (all->str[i] == '\"')
			all->str = ft_double_quote(all, &i);
	}
	printf("----------------------------\n");
	printf("string after parsing %s\n", str);
}

int 	main(void)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		close_prog(all, "error memory");
	ft_bzero(all, sizeof(t_all));
	all->str = ft_strdup("aaaaaa'dd\\dd'vvvvv\\'vrve'eferfre'4545'666");
	printf("input string %s\n", all->str);
	printf("------------------------------\n");
	ft_parser(all);
	return (0);
}