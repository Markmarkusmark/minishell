#include "../include/minishell.h"

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

int 	ft_notenv(t_msh *msh, int i, int j)
{
	t_line_symbol	*s1;
	t_line_symbol	*s2;

	s1 = ft_mshsubstr(msh, i - 1);
	if (!s1)
		return (0);
	s2 = ft_mshstrjoin(s1, &msh->line[j]);
	if (!s2)
		return (0);
	free(msh->line);
	msh->line = s2;
	free(s1);
	return (1);
}

t_line_symbol	*ft_get_new_line(t_msh *msh)
{
	int 			i;
	t_line_symbol	*new_line;
	int 			len;

	i = -1;
	len = (int) ft_strlen(msh->val_in_dlr) + 1;
	new_line = malloc(sizeof (t_line_symbol) * len);
	if (!new_line)
		return (NULL);
	while (msh->val_in_dlr[++i])
	{
		new_line[i].c = msh->val_in_dlr[i];
		new_line[i].flag = 1;
	}
	new_line[i].c = '\0';
	return (new_line);
}

int 	ft_env(t_msh *msh, int i, int j)
{
	t_line_symbol	*s1;
	t_line_symbol	*s2;
	t_line_symbol	*s3;
	t_line_symbol	*new_line;

	new_line = ft_get_new_line(msh);
	if (!new_line)
		return (0);
	s1 = ft_mshsubstr(msh, i - 1);
	if (!s1)
		return (0);
	s2 = ft_mshstrjoin(s1, new_line);
	if (!s2)
		return (0);
	s3 = ft_mshstrjoin(s2, &msh->line[j]);
	if (!s3)
		return (0);
	if (msh->line[i].c == '?')
		free(msh->val_in_dlr);
	free(msh->line);
	msh->line = s3;
	free(s1);
	free(s2);
	free(new_line);
	return (1);
}

int 	ft_check(t_msh *msh, int begin_str, int end_str)
{
	if (msh->val_in_dlr)
	{
		if (ft_env(msh, begin_str, end_str) == 0)
			return (1);
	}
	else
	{
		if (ft_notenv(msh, begin_str, end_str) == 0)
			return (1);
	}
	return (0);
}

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
			if (ft_check(msh, begin_str, end_str) == 1)
				return (0);
			begin_str = begin_str - 2;
		}
	}
	return (1);
}