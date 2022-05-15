/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/15 15:28:51 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(int code, char *text)
{
	if (code == -1)
	{
		write(2, text, ft_strlen(text));
		write(2, " command not found\n", 20);
		exit (1);
	}
	perror(text);
	exit (1);
}

char	**paths_fill(char **paths)
{
	int		i;
	char	*tmp;

	if (!paths)
		error(errno, "malloc: ");
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			error(errno, "malloc: ");
		free(paths[i]);
		paths[i] = ft_strdup(tmp);
		if (!paths[i] || !tmp)
			error(errno, "malloc: ");
		free(tmp);
		i++;
	}
	return (paths);
}

char	**get_paths(char **envp)
{
	char	**paths;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = paths_fill(ft_split(*envp + 5, ':'));
			return (paths);
		}
		envp++;
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

char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;
	int		paths_len;
	
	paths_len = ft_paths_len(paths);
	i = 0;
	cmd = ft_strdup(cmd_flags[0]);
	if (!cmd)
		error(errno, "malloc: ");
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
				printf("command not found: %s\n", cmd_flags[0]);
			// должен выводить для всех невалидных команд, выводит только для одной
		}
	}
	return (cmd);
}

int	open_file(t_llist *fd)
{
	int	return_fd;

	return_fd = -1;

// 	add case if no redirect
	if (ft_strncmp(fd->key,"<", 1) == 0)
		return_fd = open(fd->value, O_RDONLY);
	else if (ft_strncmp(fd->key,"<<", 2) == 0)
		;
	else if (ft_strncmp(fd->key,">", 1) == 0)
		return_fd = open(fd->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ft_strncmp(fd->key,">>", 2) == 0)
		;
	else 
	{
		;
	}
	if (return_fd < 0)
	// need signal here, no exit
		strerror(errno);
	fd = fd->next;
	return (return_fd);
}


//		< infile ls | grep "smt" | wc -l > outfile
// 			имеем bp - тип t_list, content - структуры t_block_process
// 
// typedef struct s_block_process
// {
// 	char		**argv;
						// "ls"
// 
// 	t_file_info	*files;	// {0, infile}
// 						// {1, outfile}
						//
// 	int			files_count;	// мб кол-во редиректов
// 	int			argc;	// хз че это
// }	t_block_process;

void	init_child(t_child *child, t_list *bp)
{
	child->i = -1;
	child->current = 0;
	child->fd[0][0] = -1;
	child->fd[0][1] = -1;
	child->fd[1][0] = -1;
	child->fd[1][1] = -1;
	child->len = ft_lstsize(bp);
}

void	execute_cmd(t_block_process *block)
{

	char	**paths;
	char	*cmd;

	// printf("trying to execute %s\n", block->argv[0]);

	paths = get_paths(global.local_envp);
	if (!paths)
		strerror(errno);
	cmd = make_cmd(paths, block->argv);

	// printf("cmd = %s\n", block->argv[0]);

	if (execve(cmd, block->argv, global.local_envp) < 0)
		strerror(errno);
	// total_free(paths);
	// total_free(cmd_flags);
}

void	r_in(t_block_process *block, t_child *child)
{
	t_file_info	*tmp;


	tmp = block->files;
	// printf("redirect type = %d\n", tmp->redirect_type);
	// printf("filename = %s\n", tmp->file_name);
	// printf("cmd name = %s\n", block->argv[0]);

	if (tmp->redirect_type == REDIR_FROM) // "<"
		child->fd_in = open(tmp->file_name, O_RDONLY);
	else if (tmp->redirect_type == HEREDOC_FROM) // "<<"
		child->fd_in = open(tmp->file_name, O_RDONLY);
	if (child->fd_in < 0)
		strerror(errno);
	if (child->fd_in && dup2(child->fd_in, STDIN_FILENO) < 0)
		strerror(errno);
	if (child->fd_in)
		close(child->fd_in);
}

void	r_out(t_block_process *block, t_child *child)
{
	t_file_info	*tmp;

	tmp = block->files;

		if (tmp->redirect_type == REDIR_TO) // ">"
		{
			child->fd_out = open(tmp->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (tmp->redirect_type == HEREDOC_TO) // ">>"
			child->fd_out = open(tmp->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (child->fd_out < 0)
			strerror(errno);
		if (child->fd_out && dup2(child->fd_out, STDOUT_FILENO) < 0)
			strerror(errno);
		if (child->fd_out)
			close(child->fd_out);
}

void	child_labour(t_child *child, t_block_process *block, int len)
{
	// need to fill fd_in before here
	if (child->i > 0)
	{
		if (dup2(child->fd[1 - child->current][0], STDIN_FILENO) < 0)
			strerror(errno);
		close(child->fd[1 - child->current][0]);
	}
	if (child->fd_out != 0 && child->i < len - 1)
	{
		if (dup2(child->fd[child->current][1], STDOUT_FILENO) < 0)
			strerror(errno);
		close(child->fd[child->current][0]);
		close(child->fd[child->current][1]);
	}

	r_in(block, child);
	// r_out(block)
	if (block->argv[0])
		execute_cmd(block);
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

void	executor(t_list *bp)
{
	t_child			child;
	t_block_process	*block;

	child.fd_in = 0;
	child.fd_out = 1;
	init_child(&child, bp);

	while (++child.i < child.len)
	{
		block = (t_block_process *)bp->content;

		if (check_cmd_name(bp))
			block->argv++;	

		if (pipe(child.fd[child.current]) == -1)
			strerror(errno);
		child.pid = fork();
		if (child.pid)
			// sig_sig_signal();
			;
		else if (child.pid < 0)
			strerror(errno);
		else if (child.pid == 0)
			child_labour(&child, block, child.len);
		close(child.fd[1 - child.current][0]);
		close(child.fd[child.current][1]);
		if (child.pid == 0)
			exit(0);
		child.current = 1 - child.current;
		bp = bp->next;
	}
	close(child.fd[1 - child.current][0]);
	wait_child(child.len);
}

// int main(__unused int argc, __unused char **argv, __unused char **envp)
// {
// 	return (0);
// }