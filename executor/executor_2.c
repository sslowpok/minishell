/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/11 16:16:02 by sslowpok         ###   ########.fr       */
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

char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;

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
		}
	}
	return (cmd);
}

// void	execute_cmd(char **args) // "ls" "-la" 
// {

// 	char	**paths;
// 	char	*cmd;

// 	paths = get_paths(global.local_envp);
// 	if (!paths)
// 		error(errno, "Malloc: ");
// 	cmd = args[0];
// 	printf("cmd = %s\n", cmd);
// 	if (execve(cmd, args, global.local_envp) < 0)
// 		strerror(errno);
// 	// total_free(paths);
// 	// total_free(cmd_flags);
// }

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

	paths = get_paths(global.local_envp);
	if (!paths)
		strerror(errno);
	cmd = make_cmd(paths, block->argv);
	printf("cmd = %s\n", cmd);
	if (execve(cmd, block->argv, global.local_envp) < 0)
		strerror(errno);
	// total_free(paths);
	// total_free(cmd_flags);
}

void	child_labour(t_child *child, t_block_process *block, __unused int len)
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
		// close(child->fd[child->current][0]);
		// close(child->fd[child->current][1]);
	}
	
	// r_in
	// r_out
	execute_cmd(block);
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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

// make it simply work with execution of cmds to start with
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
		printf("current block = %s\n", block->argv[0]);
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
		// if (child.pid == 0)
		// 	exit(0);		// why?
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