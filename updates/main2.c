/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:36:04 by mryan             #+#    #+#             */
/*   Updated: 2021/06/26 10:34:47 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->next = NULL;
	elem->content = content;
	return (elem);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elemenet;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_elemenet = ft_lstlast(*lst);
	last_elemenet->next = new;
}

void	ft_lstdel(t_list *lst, t_list *lst_main)
{
	t_list	*temp;

	temp = lst_main;
	while (temp->next != lst)
		temp = temp->next;
	temp->next = lst->next;
	free(lst);
}

int			ft_atoi(char *str)
{
	int		res;
	int		sign;
	int		i;

	res = 0;
	sign = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') ||
			(str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10;
		res += (int)str[i] - '0';
		i++;
	}
	if (sign == 1)
		return (-res);
	else
		return (res);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (ft_strlen(src));
}

static char			**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void			ft_next_str(char **nxt_s, unsigned int *nxt_s_len, char c)
{
	unsigned int	i;

	*nxt_s += *nxt_s_len;
	*nxt_s_len = 0;
	i = 0;
	while (**nxt_s && **nxt_s == c)
		(*nxt_s)++;
	while ((*nxt_s)[i])
	{
		if ((*nxt_s)[i] == c)
			return ;
		(*nxt_s_len)++;
		i++;
	}
}

char				**ft_split(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_strs = ft_nb_strs(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_strs + 1))))
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_next_str(&next_str, &next_str_len, c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1))))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char*)str);
}
////////////////////


typedef struct      s_env
{
    char            *key;
    char            *val;
}                   t_env;

typedef struct      s_cmd
{
	char            *cmd;
	char            **args_str;
	char    separ;
	int    n_args;
	int    n_redir;
}                   t_cmd;

typedef struct  s_msh
{
    t_list      *env;
    t_list      *cmd;
	char   *str; // my input string
	char            **env_args;
	int    ret;
	int    fd_0;
	int    fd_1;
}     t_msh;

/*
	посмотреть позжн echo -n еще раз
*/
int bi_echo(char **arg, int fd)
{
	int i;

	i = 0;
	if (arg[0] == NULL)
		write(fd, "\n", 2);
	else if (strcmp(arg[0], "-n") == 0)
	{
		while (arg[i] != NULL)
		{
			write(fd, arg[i], ft_strlen(arg[i]));
			i++;
		}
	}
	else
	{
		while (arg[i] != NULL)
		{
			write(fd, arg[i], ft_strlen(arg[i]));
			write(fd, "\n", 2);
			i++;
		}
	}
	return (0);
}

/*
	изменить PWD в переменной окружения
*/
int bi_cd(char **arg, int fd)
{
	char s[100];

	//processes
	printf("%s\n", getcwd(s, 100));
	if (arg[0] == NULL)
		write(1, "wrong path", 10);
	else
	{
		if (chdir(arg[0]) != 0)
			write(1, "wrong path", 10);
	}	
	printf("%s\n", getcwd(s, 100));
	return (0);
}

/*
	мне не нравится делать такой массив, нужно подумать
*/
int bi_pwd(char **arg, int fd)
{
	char dir[100]; // ?
	
	getcwd(dir, 100);
	write(fd, dir, ft_strlen(dir));
	write(fd, "\n", 2);
	return (0);
}

/*
	работает, но возможно нужно будет скорректировать позже
*/
int bi_exit(char **arg, int fd)
{
	int n;

	if (arg[0] == NULL)
		exit(0);
	else
	{
		n = ft_atoi(arg[0]);
		while (n > 255)
			n = n % 255;
		exit(n); 
	}
}

/*
	в каком виде нужно выводить export без аргументов? уточнить
*/

void print_env(t_list *env, int fd, int declare)
{
	while (env)
	{
		t_env	*envp;

		envp = malloc(sizeof(t_env));
		envp = env->content;
		if (declare == 1)
			write(fd, "declare -x ", 11);
		write(fd, envp->key, strlen(envp->key));
		write(fd, "=", 1);
		if (envp->val != NULL)
			write(fd, envp->val, strlen(envp->val));
		write(fd, "\n", 1);
		env = env->next;
	}
}

void	ft_lstsort(t_list *lst, t_list *sorted_fin)
{
	t_list *sorted;
	t_env	*temp;
	t_env *elem1;
	t_env *elem2;
	int count;
	int i, j;
	
	sorted = malloc(sizeof(t_list));
	elem1 = malloc(sizeof(t_env));
	elem2 = malloc(sizeof(t_env));
	count = 0;
	i = 0;
	j = 0;
	sorted = lst;
	while (sorted)
	{
		count++;
		sorted = sorted->next;
	}
	sorted = lst;
	print_env(sorted, 1, 0);
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			elem1 = sorted[j].content; //  поменять ввод элементов?? 
			elem2 = sorted[j + 1].content;
			if (strcmp(elem1->key, elem2->key) > 0)
			{
				temp = elem1;
				elem1 = elem2;
				elem2 = temp;
			}
			sorted[j].content = elem1;
			sorted[j + 1].content = elem2;
			j++;
		}
		print_env(sorted, 1, 0);
		i++;
	}
	print_env(sorted, 1, 1);
}

int bi_export(char **arg, t_msh *msh, int fd) // ???????
{
	int i = 0;
	t_env	*envp;
	t_list	*sorted;

	sorted = malloc(sizeof(t_list *));

	if (arg[0] == NULL)
	{
		// sort
		ft_lstsort(msh->env, sorted);
	}
	else
	{
		while (arg[i] != NULL)
		{
			envp = malloc(sizeof(t_env));
			msh->env_args = ft_split(arg[i], '=');
			envp->key = msh->env_args[0];
    	    envp->val = msh->env_args[1];
    	    ft_lstadd_back(&msh->env, ft_lstnew(envp));
			free(msh->env_args);
			i++;
		}
	}
	return(0);
}

/*
*/
int bi_unset(char **arg, t_msh *msh, int fd)
{
	int i = 0;
	t_env	envp;
	t_env	*temp;
	t_list	*lst;

	if (arg[0] != NULL)
	{
		msh->env_args = ft_split(arg[i], '=');
		envp.key = msh->env_args[0];
    	envp.val = msh->env_args[1];
		lst = msh->env;
		while (lst)
		{
			temp = lst->content;
			if (strcmp(temp->key, envp.key) == 0)
				break;
			lst = lst->next;
		}
		ft_lstdel(lst, msh->env);
	}
	return (0);
}

/*
	сделать ennro
*/
int bi_env(char **arg, t_msh *msh, int fd)
{
	if (arg[0] == NULL)
		print_env(msh->env, fd, 0);
	else
	{
		write(fd, "No such file or directory", 25);
		write(fd, "\n", 1);		
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char *arg[] = {
	NULL
	};
	t_cmd cmd;
	cmd.cmd = "export";
	cmd.args_str = arg;
	cmd.n_args = 2;

	t_env ennv;
	ennv.key = "USER";
	ennv.val = "mryan";
	t_env ennv1;
	ennv1.key = "PWD";
	ennv1.val = "/mryan/minishell";
	t_env ennv2;
	ennv2.key = "PATH";
	ennv2.val = "secret";
	
	t_msh msh;
	msh.cmd = ft_lstnew(&cmd);
	msh.env = NULL;
	msh.env = ft_lstnew(&ennv);
	ft_lstadd_back(&msh.env, ft_lstnew(&ennv1));
	ft_lstadd_back(&msh.env, ft_lstnew(&ennv2));
	
	// начало:
	if (strcmp(cmd.cmd, "echo") == 0)
		bi_echo(cmd.args_str, 1);
	else if (strcmp(cmd.cmd, "cd") == 0) // изменить pwd в переменной окружения
		bi_cd(cmd.args_str, 1);
	else if (strcmp(cmd.cmd, "pwd") == 0)
		bi_pwd(cmd.args_str, 1);
	else if (strcmp(cmd.cmd, "export") == 0)
		bi_export(cmd.args_str, &msh, 1);
	else if (strcmp(cmd.cmd, "unset") == 0)
		bi_unset(cmd.args_str, &msh, 1);
	else if (strcmp(cmd.cmd, "env") == 0)
		bi_env(cmd.args_str, &msh, 1);
	else if (strcmp(cmd.cmd, "exit") == 0)
		bi_exit(cmd.args_str, 1);
	else
		write(1, "command not found", 18);
	return (0);
}