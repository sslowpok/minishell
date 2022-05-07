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

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;

}	t_dict;

typedef struct s_info
{
	char	*reserved_words[7];
	char	**envp;
	t_dict	*envp_list;
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
	char	*path;
	char	**envp;
	int		fd[2];
	int		fd_in;
	int		fd_out;
}			t_child;

typedef struct s_command	//	struct for exacute commands
{
	// envp можно в глобалку
	char	**envp;

	int					count;
	t_dict				*fd_in; // key - redirect type (<, <<, >, >>), value - filename
	t_dict				*fd_out; // key - redirect type (<, <<, >, >>), value - filename
	char				*name;
	struct s_command	*next;
}		t_command;

#endif