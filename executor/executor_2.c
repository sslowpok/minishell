/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/18 18:50:36 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

void	handler(int code)
{
	if (code == SIGINT)
		write(1, "\n💀 > ", 8);
	if (code == SIGQUIT)
	{
		printf("\033[A\n💀 > exit\n");
		exit(0);
	}
}

void	wait_child(int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		waitpid(-1, 0, 0);
		i++;
	}
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// void	error(int code, char *text)
// {
// 	if (code == -1)
// 	{
// 		write(2, text, ft_strlen(text));
// 		write(2, " command not found\n", 20);
// 		exit (1);
// 	}
// 	strerror(errno);
// 	exit (1);
// }

char	**paths_fill(char **paths)
{
	int		i;
	char	*tmp;

	if (!paths)
		strerror(errno);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			strerror(errno);
		free(paths[i]);
		paths[i] = ft_strdup(tmp);
		if (!paths[i] || !tmp)
			strerror(errno);
		free(tmp);
		i++;
	}
	return (paths);
}

char	**get_paths()
{
	char	**paths;
	t_llist	*list;

	list = global.envp_list;
	while (list)
	{
		if (ft_strcmp(list->key, "PATH") == 0)
		{
			paths = paths_fill(ft_split(list->value, ':'));
			return (paths);
		}
		list = list->next;
	}
	return (0);
}

int	ft_paths_len(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}




// если ls + несуществующий файл, не меняется last return



char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;
	int		paths_len;
	
	paths_len = ft_paths_len(paths);
	i = 0;
	cmd = ft_strdup(cmd_flags[0]);
	if (!cmd)
		strerror(errno);
	if (!access(cmd, F_OK))
		return (cmd);
	else
	{
		free(cmd);
		while (paths[i])
		{
			cmd = ft_strjoin(paths[i], cmd_flags[0]);
			if (!access(cmd, F_OK))
				break ;
			free(cmd);
			i++;
			if (i == paths_len)
			{
				printf("command not found: %s\n", cmd_flags[0]);
				// wait_child(2);
			}
		}
	}
	return (cmd);
}

void	init_child(t_child *child, t_list *bp)
{
	child->i = -1;
	child->current = 0;
	child->fd[0][0] = -1;
	child->fd[0][1] = -1;
	child->fd[1][0] = -1;
	child->fd[1][1] = -1;
	child->fd_in = 0;
	child->fd_out = 0;
	child->len = ft_lstsize(bp);
}

int	check_if_builtin(t_block_process *block)
{	
	if (!ft_strcmp(block->argv[0], "echo"))
		return (1);
	if (!ft_strcmp(block->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp(block->argv[0], "unset"))
		return (1);
	if (!ft_strcmp(block->argv[0], "env"))
		return (1);
	if (!ft_strcmp(block->argv[0], "export"))
		return (1);
	if (!ft_strcmp(block->argv[0], "exit"))
		return (1);
	return (0);
}

int	execute_cmd(t_block_process *block, pid_t pid)
{
	char	**paths;
	char	*cmd;

	paths = NULL;
	cmd = NULL;
	paths = get_paths();
	if (!paths)
	{
		ft_putstr_fd(block->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (1);
	}
	if (!check_if_builtin(block))
	{
		cmd = make_cmd(paths, block->argv);
		if (!cmd)
			waitpid(pid, NULL, 0);
		if (execve(cmd, block->argv, global.local_envp) < 0)
			strerror(errno);
		return (0);
	}
	// }
	// printf("cmd = %s\n", block->argv[0]);

	// total_free(paths);
	// total_free(cmd_flags);
	return (1);
}



int	files_len(t_file_info *info)
{
	int	i;

	i = 0;
	while (info[i].file_name)
	{
		i++;
	}
	return (i);
}

void	r_in(t_block_process *block, t_child *child)
{
	t_file_info	*tmp;
	int			i;
	
	i = 0;
	tmp = block->files;
	// printf("redirect type = %d\n", tmp->redirect_type);
	// printf("filename = %s\n", tmp->file_name);
	// printf("cmd name = %s\n", block->argv[0]);
	while (i < block->files_count)
	{
		if (tmp[i].redirect_type == REDIR_FROM) // "<"
			child->fd_in = open(tmp[i].file_name, O_RDONLY);
		else if (tmp[i].redirect_type == HEREDOC_FROM) // "<<"
			child->fd_in = open(tmp[i].file_name, O_RDONLY);
		if (child->fd_in < 0)
			strerror(errno);
		i++;
	}
	if (child->fd_in)
	{
		if (dup2(child->fd_in, STDIN_FILENO) < 0)
			strerror(errno);
		close (child->fd_in);
	}
}

void	cut_argv(t_block_process *block)
{
	int	i;

	i = 0;
	while (block->argv[i])
	{
		if (ft_strcmp(block->argv[i], block->files->file_name) == 0)
			block->argv[i] = NULL;
		i++;
	}
}

void	r_out(t_block_process *block, t_child *child)
{
	t_file_info	*tmp;
	int	i;

	i = 0;
	tmp = block->files;
	while (i <= block->files_count + 1)
	{
		if (tmp[i].redirect_type == REDIR_TO) // ">"
		{
			child->fd_out = open(tmp[i].file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			cut_argv(block);
		}
		else if (tmp[i].redirect_type == HEREDOC_TO) // ">>"
		{
			child->fd_out = open(tmp[i].file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
			cut_argv(block);
		}
		i++;
	}
	if (child->fd_out < 0)
		strerror(errno);
	if (child->fd_out && dup2(child->fd_out, STDOUT_FILENO) < 0)
		strerror(errno);
	if (child->fd_out)
		close(child->fd_out);
}

int	child_labour(t_child *child, t_block_process *block, int len)
{
	if (child->i > 0)
	{
		if (dup2(child->fd[1 - child->current][0], STDIN_FILENO) < 0)
			strerror(errno);
		close(child->fd[1 - child->current][0]);
	}
	if (child->i < len - 1)
	{
		if (dup2(child->fd[child->current][1], STDOUT_FILENO) < 0)
			strerror(errno);
		close(child->fd[child->current][0]);
		close(child->fd[child->current][1]);
	}

	r_in(block, child);
	r_out(block, child);
	if (block->argv[0])
	{
		if (execute_cmd(block, child->pid) == 1)
			return (1);
	}
	return (0);	
}



int	check_cmd_name(t_list *bp)
{
	t_block_process	*block;

	block = (t_block_process *)bp->content;
	if (block->files_count == 0)
		return (0);
	if (!ft_strcmp(block->argv[0],  block->files[0].file_name))
		return (1);		
	return (0);
}

void	builtin_execute(t_block_process *block)
{
	if (!ft_strcmp(block->argv[0], "env"))
		ft_env(block->argv);
	if (!ft_strcmp(block->argv[0], "unset"))
		ft_unset(block, global.envp_list);
	if (!ft_strcmp(block->argv[0], "echo"))
		ft_echo(block->argv);
	if (!ft_strcmp(block->argv[0], "pwd"))
		ft_pwd(block->argv, global.envp_list);
	if (!ft_strcmp(block->argv[0], "export"))
		ft_export(block);
	if (!ft_strcmp(block->argv[0], "exit"))
		ft_exit(block->argv, global.envp_list);
}

void	r_out_builtin(t_block_process *block)
{
	t_file_info	*tmp;
	int			i;

	global.builtin_fd = 1;
	i = 0;
	tmp = block->files;
	while (i < block->files_count)
	{
		if (tmp->redirect_type == REDIR_TO)
		{
			global.builtin_fd = open(tmp[i].file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			cut_argv(block);
		}
		else if (tmp->redirect_type == HEREDOC_TO)
		{
			global.builtin_fd = open(tmp[i].file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
			cut_argv(block);
		}
		i++;
	}
	if (global.builtin_fd < 0)
	{
		global.last_return = 1;
		strerror(errno);
	}
}

int	builtin_labour(t_child *child, t_block_process *block, int len)
{
	if (child->i > 0)
	{
		if (dup2(child->fd[1 - child->current][0], STDIN_FILENO) < 0)
			strerror(errno);
		close(child->fd[1 - child->current][0]);
	}
	if (child->i < len - 1)
	{
		if (child->i != child->len - 1)
		{
			if (dup2(child->fd[child->current][1], STDOUT_FILENO) < 0)
				strerror(errno);
		}
		close(child->fd[child->current][0]);
		close(child->fd[child->current][1]);
	}
	// r_in_builtin(block);
	// r_out_builtin(block);
	r_out_builtin(block);
	builtin_execute(block);
	return (0);
}

void	new_executor(t_list *bp)
{
	t_child	child;
	t_block_process	*block;

	init_child(&child, bp);

	while (++child.i < child.len)
	{
		
		block = (t_block_process *)bp->content;
		if (check_cmd_name(bp))
			block->argv++;
		if (pipe(child.fd[child.current]) == -1)
			strerror(errno);
		if (check_if_builtin(block) == 1)
			builtin_labour(&child, block, child.len);		
		else
		{
			child.pid = fork();
			if (child.pid == 0)
				if (child_labour(&child, block, child.len) == 1)
					waitpid(child.pid, NULL, 0);
			if (child.pid)
				sig_sig_signal();
			close(child.fd[1 - child.current][0]);
			close(child.fd[child.current][1]);
			child.current = 1 - child.current;
		}
		bp = bp->next;
	}
	close(child.fd[1 - child.current][0]);
	wait_child(child.len);
}
