/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 18:56:32 by mryan             #+#    #+#             */
/*   Updated: 2021/07/21 20:17:50 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_rdr_signal(t_msh *msh, int *status)
{
	msh->return_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (*status == 2)
		{
			rl_on_new_line();
			printf("\b\b");
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line();
		}
		if (*status == 3)
		{
			rl_on_new_line();
			rl_redisplay();
			printf("\b\b");
			printf("");
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	ft_free_rdr(t_rdr *rdr, t_com *com, int *num)
{
	while (*num < com->num_redir)
	{
		if (rdr[*num].kind != NULL)
			free(rdr[*num].kind);
		if (rdr[*num].arg != NULL)
			free(rdr[*num].arg);
		num++;
	}
}
