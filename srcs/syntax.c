#include "../include/minishell.h"

int	ft_check_token1(t_msh *msh, int *len)
{
	if (msh->token)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 1);
		return (1);
	}
	if (msh->line[*len].symb == ';')
		msh->token = ';';
	if (msh->line[*len].symb == '|')
		msh->token = '|';
	++*len;
	return (0);
}

int	ft_check_token2(t_msh *msh, int *len)
{
	int j;

	if (msh->token == '!')
	{
		ft_putstr_fd("syntax error near unexpected token 'redirect'\n", 1);
		return (1);
	}
	msh->token = '!';
	j = *len;
	if (msh->line[*len].symb == '>')
	{
		while (msh->line[*len].symb == '>' && (*len - j) <= 1 && msh->line[*len].flag == 0)
			++*len;
	}
	if (msh->line[*len].symb == '<')
	{
		while (msh->line[*len].symb == '<' && (*len - j) <= 1 && msh->line[*len].flag == 0)
			++*len;
	}
	return (0);
}

int	ft_check_token3(t_msh *msh, int *len)
{

	if ((msh->line[*len].symb == '<' && msh->line[*len].flag == 0) ||
			(msh->line[*len].symb == '>' && msh->line[*len].flag == 0) ||
			(msh->line[*len].symb == ';' && msh->line[*len].flag == 0) ||
			(msh->line[*len].symb == '|' && msh->line[*len].flag == 0) ||
			(msh->line[*len].symb == ' ' && msh->line[*len].flag == 0) ||
											(msh->line[*len].symb == '\0'))
		return (0);
	else
		return (1);
}

int	t_get_token(t_msh *msh, int *len)
{
	while (msh->line[*len].symb)
	{
		if ((msh->line[*len].symb == ';' || msh->line[*len].symb == '|') && msh->line[*len].flag == 0)
		{
			if (ft_check_token1(msh, len))
				return (1);
		}
		else if ((msh->line[*len].symb == '>' || msh->line[*len].symb == '<') && msh->line[*len].flag == 0)
		{
			if (ft_check_token2(msh, len))
				return (1);
			if ((msh->line[*len].symb == '>' || msh->line[*len].symb == '<') && msh->line[*len].flag == 0)
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
		while (msh->line[*len].symb == ' ' && msh->line[*len].flag == 0)
			++*len;
	}
	return (0);
}

int	ft_check_line_syntax(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->line[i].symb == ' ' && msh->line[i].flag == 0)
		i++;
	if (msh->line[i].symb == ';' && msh->line[i].flag == 0)
	{
		ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
		return (1);
	}
	if (msh->line[i].symb == '|' && msh->line[i].flag == 0)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		return (1);
	}
	if (ft_get_token(msh, &i))
		return (1);
	if (ft_check_token_error(msh))
		return (1);
	return (0);
}
