/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/11 11:58:21 by sslowpok         ###   ########.fr       */
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

void	execute_cmd(char **args) // "ls" "-la" 
{

	char	**paths;
	char	*cmd;

	paths = get_paths(global.local_envp);
	if (!paths)
		error(errno, "Malloc: ");
	cmd = args[0];
	printf("cmd = %s\n", cmd);
	if (execve(cmd, args, global.local_envp) < 0)
		strerror(errno);
	// total_free(paths);
	// total_free(cmd_flags);
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

// void	processes(t_child *child, t_list *bp)
// {

// 	pid_t	pid;
// 	t_block_process *block;

// 	block = (t_block_process *)bp->content;
// 	if (pipe(child->fd) < 0)
// 		strerror(errno);
// 	pid = fork();
// 	if (pid < 0)
// 		strerror(errno);
	
// 	else if (pid == 0)
// 	{
// 	printf("was here\n");

// 		close(child->fd[0]);
// 		if (dup2(child->fd[1], STDOUT_FILENO) < 0)
// 			strerror(errno);
// 		close (child->fd[1]);
// 		execute_cmd(block->argv);
// 	}
// 	else
// 	{
// 		close(child->fd[1]);
// 		if (dup2(child->fd[0], STDIN_FILENO) < 0)
// 			strerror(errno);
// 		close (child->fd[0]);
// 		// пофиксить пипех для waitpid
// 		waitpid(pid, NULL, 0);
// 	}
// }


//		< infile ls | grep "smt" | wc -l > outfile
// 			имеем bp - тип t_list, content - структуры t_block_process
// 
// typedef struct s_block_process
// {
// 	char		**argv;
						// "ls"
						// "grep" "smt"
						// "wc" "-l"
// 
// 	t_file_info	*files;	// {0, infile}
// 						// {1, outfile}
						//
// 	int			files_count;	// мб кол-во редиректов
// 	int			argc;	// хз че это
// }	t_block_process;

void	executor(t_list *bp)
{
	t_child	child;
	t_block_process	*block;
	pid_t	pid;
	int	i;

	i = 0;
	child.fd_in = 0;
	child.fd_out = 1;

	while (bp)
	{
		block = (t_block_process *)bp->content;
		if (block->files)
		{
			// case if first and last block of bp
			child.fd_in = open(block->files->file_name, O_RDONLY);
			if (dup2(child.fd_in, STDIN_FILENO) < 0)
				strerror(errno);
		}
		if (pipe(child.fd[i]) == -1)
			strerror(errno);
		pid = fork();
		if (pid < 0)
			strerror(errno);
		else if (pid == 0)
		{
			// child_work
		}
		else
		{
			// parent_work
		}

		// processes(&child, bp);
		bp = bp->next;
		i++;
	}



}

// int main(__unused int argc, __unused char **argv, __unused char **envp)
// {
// 	return (0);
// }