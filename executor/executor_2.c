/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/08 14:18:57 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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

void	execute_cmd(char *arg, char **envp) // "ls -la" 
{
	char	**paths;
	char	**cmd_flags;
	char	*cmd;

	paths = get_paths(envp);
	if (!paths)
		error(errno, "Malloc: ");
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error(errno, "Malloc: ");
	cmd = make_cmd(paths, cmd_flags);
	if (!cmd)
		error(errno, "Malloc: ");
	if (execve(cmd, cmd_flags, envp) < 0)
		error(-1, cmd_flags[0]);
	// total_free(paths);
	// total_free(cmd_flags);
}

int	ft_cmdlen(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	init_child(t_child *child, t_command *cmd)
{
	child->i = -1;
	child->fd[0] = -1;
	child->fd[1] = -1;
	child->envp = cmd->envp;
	child->len = ft_cmdlen(cmd);
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

void	processes(t_child *child, t_command *cmd)
{
	pid_t	pid;

	if (pipe(child->fd) < 0)
		strerror(errno);
	pid = fork();
	if (pid < 0)
		strerror(errno);
	else if (pid == 0)
	{
		close(child->fd[0]);
		if (dup2(child->fd[1], STDOUT_FILENO) < 0)
			strerror(errno);
		close (child->fd[1]);
		execute_cmd(cmd->name, cmd->envp);
	}
	else
	{
		close(child->fd[1]);
		if (dup2(child->fd[0], STDIN_FILENO) < 0)
			strerror(errno);
		close (child->fd[0]);
	}
}

void	executor(t_command *cmd)
{
	t_child	child;
	
	init_child(&child, cmd);
	child.fd_in = open_file(cmd->fd_in);
	if (dup2(child.fd_in, STDIN_FILENO) < 0)
		strerror(errno);
	// child.fd_out = 
	// if (dup2(child.fd_out, STDOUT_FILENO) < 0)
	// strerror(errno);
	while (++child.i < child.len)
	{
		processes(&child, cmd);
		cmd = cmd->next; // needed or not?
	}
	// execute_cmd(last cmd);
}

// int main(__unused int argc, __unused char **argv, __unused char **envp)
// {
// 	return (0);
// }