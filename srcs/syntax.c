#include "../include/minishell.h"

void 	ft_check_token1(t_msh *msh, int *len)
{
	if (msh->line[*len].c == ';')
		msh->token = ';';
	if (msh->line[*len].c == '|')
		msh->token = '|';
	*len = *len + 1;
}

void	ft_check_token2(t_msh *msh, int *len)
{
	int j;

	msh->token = '!';
	j = *len;
	if (msh->line[*len].c == '>')
	{
		while (msh->line[*len].c == '>' && (*len - j) <= 1 && msh->line[*len].flag == 0)
			*len = *len + 1;
	}
	if (msh->line[*len].c == '<')
	{
		while (msh->line[*len].c == '<' && (*len - j) <= 0 && msh->line[*len].flag == 0)
			*len = *len + 1;
	}
}

int		ft_get_token(t_msh *msh, int *len)
{
	while (msh->line[*len].c)
	{
		if ((msh->line[*len].c == ';' || msh->line[*len].c == '|') && msh->line[*len].flag == 0)
		{
			if (msh->token)
			{
				ft_putstr_fd("syntax error near unexpected token `;' or '|'", 1);
				return (1);
			}
			ft_check_token1(msh, len);
		}
		else if ((msh->line[*len].c == '>' || msh->line[*len].c == '<') && msh->line[*len].flag == 0)
		{
			if (msh->token == '!')  // ! - это редирект тут
			{
				ft_putstr_fd("syntax error near unexpected token '>' or '<'", 1);
				return (1);
			}
			ft_check_token2(msh, len);
			if ((msh->line[*len].c == '>' || msh->line[*len].c == '<') && msh->line[*len].flag == 0)
			{
				ft_putstr_fd("syntax error near unexpected token '>' or '<'", 1);
				return (1);
			}
		}
		// продолжаю тут

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
		ft_putstr_fd("syntax error near unexpected token `;'", 1);
		return (1);
	}
	if (msh->line[i].c == '|' && msh->line[i].flag == 0)
	{
		ft_putstr_fd("syntax error near unexpected token `|'", 1);
		return (1);
	}
	// останавливаюсь на том чтобы получить флаг
	if (ft_get_token(msh, &i) == 1)
		return (1);
}