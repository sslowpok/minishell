/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/07 15:51:32 by sslowpok         ###   ########.fr       */
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

void	execute_cmd(char *arg, char **envp)
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

void	init_child(t_child *child, t_command *cmd)
{
	child->i = -1;
	child->fd[0] = -1;
	child->fd[1] = -1;
	child->envp = cmd->envp;
	
}

int	open_file(t_dict *fd)
{
	int	return_fd;

	if (fd->key == "<")
		return_fd = open(fd->value, O_RDONLY);
	else if (fd->key == "<<")
		;
	else if (fd->key == ">")
		;
	else if (fd->key == ">>")
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

void	executor(t_command *cmd)
{
	t_child	child;
	
	init_child(&child, cmd);
	child.fd_in = open_file(cmd->fd_in);
}

int main(int argc, char **argv, char **envp)
{
	execute_cmd("yes", envp);
}