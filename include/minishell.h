#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "fcntl.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

# define MINISHELL_LOOP 1
# define ITS_ARG 4
# define ITS_RDR 3
# define NONE -1

typedef struct s_env
{
	char			*key;
	char			*val;
}					t_env;

typedef struct s_line_symbol
{
	char			symb;
	int				flag;
}					t_line_symbol;

typedef struct s_com
{
	int				num_args;
	int				num_redir;
	char			*com;
	char			**args_new;
	char			pipe_out;
	char			pipe_in;
	t_line_symbol	**args;
}					t_com;

typedef struct s_rdr
{
	char			*kind;
	char			*arg;
}					t_rdr;

typedef struct s_sort
{
	int				i;
	int				j;
	int				count;
}					t_sort;

typedef struct s_msh
{
	t_list			*env;
	t_list			*com;
	t_line_symbol	*line;
	char			*str;
	char			**env_args;
	char			*val_in_dlr;
	int				return_code;
	char			token;
	int				fd_0;
	int				fd_1;
	int				pipe_fd[2];
	int				pipe_read_fd;
	int				rdr_type[2];
	int				rdr_fd[2];
	int				rdr_fd2[2];
	int				numwaits_pipe;
}					t_msh;

t_list			*g_mem;

t_line_symbol	*ft_mshsubstr(t_msh *msh, size_t len);
int				ft_mshstrlen(t_line_symbol *line);
t_line_symbol	*ft_mshstrjoin(t_line_symbol *line1, t_line_symbol *line2);
void			close_prog(char *err);
void			ft_clear_oldpwd(t_msh *msh);
void			ft_environment(t_msh *msh, char **env);
int				ft_get_quote_flag(t_msh *msh, const int *i, int q_flag);
int				ft_check_open_quote(int q_flag);
int				ft_line_size(t_msh *msh);
int				ft_get_symbol_flag_utils(t_msh *msh, const int *i, int qte);
int				ft_get_symbol_flag(t_msh *msh, int *len, int *qte, int *dlr);
t_line_symbol	*ft_get_struct_line(t_msh *msh, int mlc_len);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_get_env(t_msh *msh, char *val);
int				ft_get_val_in_dlr(t_msh *msh, t_line_symbol *line);
int				ft_notenv(t_msh *msh, int i, int j);
t_line_symbol	*ft_get_new_line(t_msh *msh);
int				ft_envir(t_msh *msh, int i, int j);
int				ft_check(t_msh *msh, int begin_str, int end_str);
int				ft_get_dollar(t_msh *msh);
int				ft_preparser(t_msh *msh);
void			ft_handle_process(t_msh *msh);
int				ft_check_line_syntax(t_msh *msh);
int				ft_check_token_error(t_msh *msh);
int				ft_get_token(t_msh *msh, int *len);
int				ft_check_token3(t_msh *msh, int *len);
int				ft_check_token2(t_msh *msh, int *len);
int				ft_check_token1(t_msh *msh, int *len);
void			ft_parser(t_msh *msh);
void			ft_command_manage(t_msh *msh);
int				ft_binary(t_msh *msh);
void			ft_builtin(t_msh *msh, t_com *com);
void			ft_lstdel(t_list *lst, t_list *lst_main);
int				ft_redir_checker(t_com *com);
void			ft_rdr_count(t_com *com);
void			ft_redir_mng(t_com *com, t_msh *msh);
int				ft_get_result(t_rdr *rdr, t_com *com, int num, int i);
int				ft_loop(t_rdr *rdr, t_com *com);
void			ft_launch_com(t_msh *msh, t_com *com);
void			ft_echo(t_msh *msh, t_com *com);
void			ft_cd(t_msh *msh, t_com *com);
void			ft_pwd(t_msh *msh);
//void			ft_print_env(t_list *env);
void			ft_env(t_msh *msh, t_com *com);
int				ft_export(t_msh *msh, t_com *com);
void			ft_copy_lst(t_list *lst, t_list **new);
void			ft_unset(t_msh *msh, t_com *com);
void			ft_exit(t_msh *msh, t_com *com);
void			free_arr(char **arr);
void			rl_replace_line(const char *a, int b);
void			ft_exec_all(t_msh *msh, t_com *com);
void			ft_pipe_out(t_msh *msh, t_com *com);
void			ft_pipe_in(t_msh *msh, t_com *com, pid_t *pidpipe);
void			ft_check_wait(t_msh *msh, t_com *com, pid_t *pidpipe);
char			*ft_get_line_from_struct(t_line_symbol *line,
					int beg, int size);
int				ft_mshcmp(t_line_symbol *l1, char *l2);
char			**ft_create_argv(t_msh *msh, t_com *com);
char			**ft_get_paths(t_msh *msh);
char			*ft_join_com(t_msh *msh, t_com *com, char *path);
int				ft_get_envs_values(t_env *lst, char **env);
void			free_arr(char **arr);
int				ft_check_token_error(t_msh *msh);
int				ft_check_symbol(t_line_symbol line);
int				ft_get_num_of_args(t_line_symbol *line);
t_line_symbol	*ft_get_clean_line(t_line_symbol *line);
int				ft_pass_str(int *i, t_msh *msh);
t_line_symbol	*ft_mshsubstr2(t_msh *msh, int n, size_t len);
void			handle_signals(int signo);
char			**ft_get_envs(t_msh *msh);
int				ft_redir_checker(t_com *com);
void			ft_file_check_utils(t_msh *msh, t_rdr rdr,
					int rdr_num, int *fd);
void			ft_launch_rdr_utils(t_msh *msh, t_com *com, int fd[2]);
t_line_symbol	*ft_mshdup(t_line_symbol *line);
void			ft_skip_spaces_in_line(t_msh *msh, int *i);
void			ft_split_line(t_msh *msh, t_com *command, int *i);
void			ft_init_proc(t_com **command, t_list **new_list);
void			ft_get_separator(t_msh *msh, t_com *command, int separ, int *i);
int				ft_get_args(t_msh *msh, t_com *cmd, int *i);
char			*ft_get_str_from_struct(t_line_symbol *line, int len);
int				ft_update_line(t_line_symbol ***str, t_com *cmd,
					int num, int its_cmd);
void			ft_check_if_command(t_com *command, int its_cmd);
int				ft_get_command(t_com *command);
void			ft_redir_mng_utils(t_com *com, t_msh *msh,
					int *delete, t_rdr *rdr);
int				ft_file_check(t_msh *msh, t_rdr rdr, int rdr_num);
void			ft_execute_rdr(t_msh *msh, t_rdr *rdr, t_com *com);
void			ft_not_file_after_rdr(t_msh *msh, t_rdr *rdr, t_com *com);
void			ft_launch_rdr_utils_1(t_msh *msh, t_rdr *rdr, char *out);
int				ft_get_symbol_flag(t_msh *msh, int *i, int *qte, int *dlr);
t_line_symbol	*ft_get_struct_line(t_msh *msh, int mlc_len);
int				ft_get_token_utils(t_msh *msh, int *len);
void			del_lst(void *env);
void	ft_print_env(t_list *env, int fd, int declare);

#endif
