/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:12:31 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/02 13:56:36 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex_bonus.h"

// typedef struct s_command	//	struct for exacute commands
// {
// 	char	*cmd;
// 	char	**cmd_flags;
// 	char	*envp;
// }		t_command;

void	error(int code)
{
	ft_putendl_fd(strerror(code), 2);
}

int	open_file(char *arg, int code)
{
	int	fd;

	fd = -1;
	if (code == 1)
	{
		fd = open(arg, O_RDONLY);
		if (fd < 0)
			error(errno);
	}
	else if (code == 2)
	{
		fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			error(errno);
	}
	return (fd);
}

void	processes(t_child *child, t_command *command)
{
	pid_t	pid;

	if (pipe(child->fd) < 0)
		error(errno);
	pid = fork();
	if (pid < 0)
		error(errno);
	else if (pid == 0)
	{
		close(child->fd[0]);
		if (dup2(child->fd[1], STDOUT_FILENO) < 0)
			error(errno);
		close(child->fd[1]);
		// exec_cmd();
	}
	else
	{
		close(child->fd[1]);
		if (dup2(child->fd[0], STDOUT_FILENO) < 0)
			error(errno);
		close(child->fd[0]);
	}
}

/*
** function that executes commands
*/
void	execute_cmd(t_command *command)
{
	t_child	child;
	int		i;

	i = 2;
	child.fd_in = open_file(command->file_name, 1);
	if (dup2(child.fd_in, STDIN_FILENO) < 0)
		error(errno);
	// need to add case to redirect fd_out if needed
	// if (dup2(child.fd_out, STDOUT_FILENO) < 0)
		// error(errno);
	child.fd_out = 1;
	// need to fix i and add correct command execution
	while (i < command->files_count)
	{
		processes(&child, command);
		i++;
	}
}

int	main(void)
{
	t_command	command;
	
	command.cmd = "ls";
	command.file_name = "test_file";

	
	execute_cmd(&command);
	return (0);
}