#include "../include/minishell.h"

int 	ft_check_token1(t_msh *msh, int *len)
{
	if (msh->token)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 1);
		return (1);
	}
	if (msh->line[*len].c == ';')
		msh->token = ';';
	if (msh->line[*len].c == '|')
		msh->token = '|';
	++*len; //*len = *len + 1;
	return (0);
}

int		ft_check_token2(t_msh *msh, int *len)
{
	int j;

	if (msh->token == '!')  // ! - это редирект тут
	{
		ft_putstr_fd("syntax error near unexpected token 'redirect'\n", 1);
		return (1);
	}
	msh->token = '!';
	j = *len;
	if (msh->line[*len].c == '>')
	{
		while (msh->line[*len].c == '>' && (*len - j) <= 1 && msh->line[*len].flag == 0)
			++*len; //*len = *len + 1;
	}
	if (msh->line[*len].c == '<')
	{
		while (msh->line[*len].c == '<' && (*len - j) <= 0 && msh->line[*len].flag == 0)
			++*len; //*len = *len + 1;
	}
	return (0);
}

int		ft_check_token3(t_msh *msh, int *len)
{

	if ((msh->line[*len].c == '<' && msh->line[*len].flag == 0) ||
			(msh->line[*len].c == '>' && msh->line[*len].flag == 0) ||
			(msh->line[*len].c == ';' && msh->line[*len].flag == 0) ||
			(msh->line[*len].c == '|' && msh->line[*len].flag == 0) ||
			(msh->line[*len].c == ' ' && msh->line[*len].flag == 0) ||
											(msh->line[*len].c == '\0'))
		return (0);
	else
		return (1);
}

int		ft_get_token(t_msh *msh, int *len)
{
	while (msh->line[*len].c)
	{
		if ((msh->line[*len].c == ';' || msh->line[*len].c == '|') && msh->line[*len].flag == 0)
		{
			if (ft_check_token1(msh, len))
				return (1);
		}
		else if ((msh->line[*len].c == '>' || msh->line[*len].c == '<') && msh->line[*len].flag == 0)
		{
			if (ft_check_token2(msh, len))
				return (1);
			if ((msh->line[*len].c == '>' || msh->line[*len].c == '<') && msh->line[*len].flag == 0)
			{
				ft_putstr_fd("syntax error near unexpected token 'redirect'\n", 1);
				return (1);
			}
		}
		else
		{
			msh->token = 0;
			if (ft_check_token3(msh, len))
				++*len;
		}
		while (msh->line[*len].c == ' ' && msh->line[*len].flag == 0)
			++*len;
	}
	return (0);
}

int		ft_check_token_error(t_msh *msh)
{
	if (msh->token == '!')
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
		return (1);
	}
	if (msh->token == '|')
	{
		ft_putstr_fd("open pipe\n", 1);
		return (1);
	}
	return (0);
}

int		ft_check_line_syntax(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->line[i].c == ' ' && msh->line[i].flag == 0)
		i++;
	if (msh->line[i].c == ';' && msh->line[i].flag == 0)
	{
		ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
		return (1);
	}
	if (msh->line[i].c == '|' && msh->line[i].flag == 0)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		return (1);
	}
	// останавливаюсь на том чтобы получить флаг
	if (ft_get_token(msh, &i))
		return (1);
	if (ft_check_token_error(msh))
		return (1);
	return (0);
}