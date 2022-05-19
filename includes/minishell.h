#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include "../libft/libft.h"

// typedef int(*t_builtin_ptr)(t_list*, t_info*);

# define REDIR_FROM		2 // <
# define REDIR_TO		4 // >
# define HEREDOC_FROM	3 // <<
# define HEREDOC_TO		1 // >>

typedef struct s_llist
{
	char			*key;
	char			*value;
	struct s_llist	*next;

}	t_llist;

typedef struct s_info
{
	char	*reserved_words[7];
	char	**envp;
	t_llist	*envp_list;
	int		envp_f;
	int		exit_f;
	int		status;
}		t_info;

typedef struct s_file_info
{
	int		redirect_type;
	char	*file_name;
}	t_file_info;


typedef struct s_block_process
{
	char		**argv; // "ls" "-la"
	t_file_info	*files;	// {0, filename}
	int			files_count;	// мб кол-во редиректов
	int			argc;	// хз че это
}	t_block_process;

typedef struct s_child
{
	// int		i;
	int		len;
	int		current;
	int		i;
	char	*path;

	// char	**envp;
	
	pid_t	pid;
	int		fd[2][2];
	int		fd_in;
	int		fd_out;
}			t_child;

typedef struct s_global
{
	char		**local_envp;
	t_list		*block_process; // content - t_block_process
	t_llist		*envp_list;
	// 
	// t_command	*cmd;
	int			last_return;
	int			builtin_fd;

}		t_global;

// void	executor(t_list *bp);
void	new_executor(t_list *bp);
void	handler(int code);
void	sig_sig_signal(void);
char	**paths_fill(char **paths);
char	**get_paths();
int	ft_paths_len(char **paths);
char	*make_cmd(char **paths, char **cmd_flags);

void	r_in(t_block_process *block, t_child *child);
void	r_out(t_block_process *block, t_child *child);
void	r_out_builtin(t_block_process *block);

int	builtin_labour(t_child *child, t_block_process *block, int len);
void	builtin_execute(t_block_process *block);
void	cut_argv(t_block_process *block);
int	check_if_builtin(t_block_process *block);
int	files_len(t_file_info *info);

void	wait_child(int len);
void	total_free(char **str);
void	init_child(t_child *child, t_list *bp);




t_global	global;

#endif