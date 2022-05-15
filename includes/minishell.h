#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

// typedef int(*t_builtin_ptr)(t_list*, t_info*);

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
	// maybe needed ptr
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
	char		**argv;
	t_file_info	*files;
	int			files_count;
	int			argc;
}	t_block_process;

typedef struct s_global
{
	char		**local_envp;
	t_list		*block_process; // content - t_block_process
	t_llist		*envp_list;
	// 
	// t_command	*cmd;
	int			last_return;

}		t_global;

t_global	global;
void	pipex(int argc, char **argv, char **envp);

#endif