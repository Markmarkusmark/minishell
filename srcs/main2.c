#include "../include/minishell.h"

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
			write(fd, "\n", 1);
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
	//printf("%s\n", getcwd(s, 100));
	if (arg[0] == NULL)
		write(1, "wrong path", 10);
	else
	{
		if (chdir(arg[0]) != 0)
			write(1, "wrong path", 10);
	}	
	//printf("%s\n", getcwd(s, 100));
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
	//write(fd, "\n", 2);
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

void	ft_pwd(t_msh *msh)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	printf("%s\n", pwd);
	free(pwd);
	msh->return_code = 0;
}

void	ft_env(t_msh *msh, t_com *com)
{
	t_list	*list;

	if (com->args_new != NULL) // иногда залетает мусор какой-ьл не знаю как пока не смог найти
	{
		ft_putstr_fd("command \"env\" shouldnt get arguments\n", 2);
		msh->return_code = 1;
		return ;
	}
	list = msh->env;
	while (list)
	{
		if (((t_env *)list->content)->val != NULL)
			printf("%s=%s\n", ((t_env *)list->content)->key,
				   ((t_env *)list->content)->val);
		list = list->next;
	}
	msh->return_code = 0;
}

int ft_builtin(t_msh *msh, t_com *com)
{
	if (ft_strcmp(com->com, "echo") == 0) // переделал , все работает как надо
		ft_echo(msh, com);
	else if (ft_strcmp(com->com, "cd") == 0) // переделал , все работает как надо
		ft_cd(msh, com);
	else if (ft_strcmp(com->com, "pwd") == 0) // переделал , все работает как надо
		ft_pwd(msh);
	else if (ft_strcmp(com->com, "env") == 0) // переделал , все работает как надо
		ft_env(msh, com);
	else if (ft_strcmp(com->com, "export") == 0) // !!! надо сделать
		bi_export(com->args_new, msh, 1);
	else if (ft_strcmp(com->com, "unset") == 0) // !!! надо сделать
		bi_unset(com->args_new, msh, 1);
	else if (ft_strcmp(com->com, "exit") == 0) // !!! надо сделать
		bi_exit(com->args_new, 1);
	else
		ft_launch_com(msh, com);
}