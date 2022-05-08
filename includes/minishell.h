#ifndef MINISHELL_H
# define MINISHELL_H

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

/*
**	pipex needs:
**	0) name of file
**
**	1) command name or full path to it:
**	examples:		"ls"	"usr/bin/ls"
**
**	2) command args:
**	examples:	"ls" "-l"	"wc" "-w"
**
**	3) envp variable, where to find "PATH=" (finds itself)
**	4) files_count from t_block_process (or number of commands?)
*/

typedef struct s_child
{
	int		i;
	int		len;
	char	*path;
	char	**envp;
	int		fd[2];
	int		fd_in;
	int		fd_out;
}			t_child;

typedef struct s_command	//	struct for exacute commands
{
	// int					count;
	// заполнить из t_file_info
	t_llist				*fd_in; // key - redirect type (<, <<, >, >>), value - filename
	t_llist				*fd_out; // key - redirect type (<, <<, >, >>), value - filename
	char				*name;
	struct s_command	*next;
}		t_command;

typedef struct s_global
{
	char		**local_envp;
	t_list		*block_process; // content - t_block_process
	// 
	// t_command	*cmd;
	int			last_return;

}		t_global;

void	execute_cmd(char *arg, char **envp); // "ls -la"
void	executor(void);
void	init_cmd(void);


t_global	global;

#endif