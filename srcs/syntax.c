#include "../include/minishell.h"

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
}