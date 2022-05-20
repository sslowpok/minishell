/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:32:23 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:42:14 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_llist	*envp_list;
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

typedef struct s_child
{
	int		len;
	int		current;
	int		i;
	char	*path;
	pid_t	pid;
	int		fd[2][2];
	int		fd_in;
	int		fd_out;
}			t_child;

typedef struct s_global
{
	char		**local_envp;
	t_list		*block_process;
	t_llist		*envp_list;
	int			last_return;
	int			builtin_fd;

}		t_global;

int			new_executor(t_list *bp);
void		handler(int code);
void		sig_sig_signal(void);
char		**paths_fill(char **paths);
char		**get_paths(void);
int			ft_paths_len(char **paths);
char		*make_cmd(char **paths, char **cmd_flags);

void		r_in(t_block_process *block, t_child *child);
void		r_out(t_block_process *block, t_child *child);
void		r_out_builtin(t_block_process *block);

int			builtin_labour(t_child *child, t_block_process *block, int len);
void		builtin_execute(t_block_process *block);
void		cut_argv(t_block_process *block);
int			check_if_builtin(t_block_process *block);
int			files_len(t_file_info *info);

void		wait_child(int len);
void		total_free(char **str);
void		init_child(t_child *child, t_list *bp);

void		help_executor(t_child *child, t_block_process *block);
int			child_labour(t_child *child, t_block_process *block, int len);

t_global	g_global;

#endif