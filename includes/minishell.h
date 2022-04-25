#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# include "../libft/libft.h"

// typedef int(*t_builtin_ptr)(t_list*, t_info*);

typedef struct s_llist
{
	void			*key;
	void			*value;
	struct s_llist	*next;

}			t_llist;

typedef struct s_info
{

	char	*reserved_words[7];
	char	**envp;

	// maybe needed ptr
	t_llist	envp_list;
	int		envp_f;
	int		exit_f;
	int		status;
}		t_info;

void	pipex(int argc, char **argv, char **envp);

#endif