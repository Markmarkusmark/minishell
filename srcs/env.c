#include "../include/minishell.h"

void	ft_copyenv(t_all *all, char **env)
{
	int		i;
	char	**env2;

	i = 0;
	while (env[i])
		i++;
	env2 = ft_calloc(sizeof(char *), i + 1);
	if (!env2)
		close_prog(all, "error memory");
	i = 0;
	while (env[i])
	{
		env2[i] = ft_strdup(env[i]);
		i++;
	}
	all->env = env2;
}