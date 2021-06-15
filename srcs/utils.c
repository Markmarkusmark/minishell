#include "../include/minishell.h"

int				ft_mshstrlen(t_line_symbol *line)
{
	int	i;

	i = 0;
	while (line[i].c)
		i++;
	return (i);
}

t_line_symbol 	*ft_mshsubstr(t_msh *msh, size_t len)
{
	size_t			i;
	size_t			j;
	t_line_symbol	*substr;

	i = -1;
	j = 0;

	if (!msh->line)
		return (NULL);
	substr = malloc(sizeof (t_line_symbol) * (len + 1));
	if (!substr)
		return (NULL);
	if (msh->line[0] == '\0')
	{
		substr[0].c = '\0';
		substr[0].flag = 0;
		return (substr);
	}
	while (++i < len)
	{
		substr[j] = msh->line[i];
		j++;
	}
	substr[j].c = '\0';
	return (substr);
}

t_line_symbol	*ft_mshstrjoin(t_line_symbol *line1, t_line_symbol *line2)
{
	t_line_symbol	*new_line;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!line1 || !line2)
		return (NULL);
	new_line = malloc(sizeof (t_line_symbol) * (ft_mshstrlen(line1) + ft_mshstrlen(line2) + 1));
	if (!new_line)
		return (NULL);
	while (line1[j].c)
	{
		new_line[i] = line1[j];
		i++;
		j++;
	}
	j = 0;
	while (line2[j].c)
	{
		new_line[i] = line2[j];
		i++;
		j++;
	}
	new_line[i].c = '\0';
	return (new_line);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	z;

	z = 0;
	while (s1[z] != '\0' || s2[z] != '\0')
	{
		if (s1[z] != s2[z])
			return ((unsigned char)s1[z] - (unsigned char)s2[z]);
		z++;
	}
	return (0);
}