/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:28:01 by sslowpok          #+#    #+#             */
/*   Updated: 2022/04/25 15:12:21 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../includes/error.h"

int	open_file(char *arg, int code)
{
	int	file;

	file = -1;
	if (code == 1)
	{
		file = open(arg, O_RDONLY);
		if (file < 0)
			error(errno, "infile: ");
	}
	else if (code == 2)
	{
		file = open(arg, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file < 0)
			error(errno, "outfile: ");
	}
	return (file);
}

void	processes(t_child *child, char *arg, char **envp)
{
	pid_t	pid;

	if (pipe(child->fd) < 0)
		error(errno, "pipe: ");
	pid = fork();
	if (pid < 0)
		error(errno, "fork: ");
	else if (pid == 0)
	{
		close(child->fd[0]);
		if (dup2(child->fd[1], STDOUT_FILENO) < 0)
			error(errno, "Dup2: ");
		close(child->fd[1]);
		execute_cmd(arg, envp);
	}
	else
	{
		close(child->fd[1]);
		if (dup2(child->fd[0], 0) < 0)
			error(errno, "Dup2:");
		close(child->fd[0]);
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	t_child	child;
	int		i;

	i = 2;
	child.fd_in = open_file(argv[1], 1);
	if (dup2(child.fd_in, STDIN_FILENO) < 0)
		error(errno, "infile: ");
	child.fd_out = open_file(argv[argc - 1], 2);
	if (dup2(child.fd_out, STDOUT_FILENO) < 0)
		error(errno, "outfile: ");
	while (i < argc - 2)
	{
		processes(&child, argv[i], envp);
		i++;
	}
	execute_cmd(argv[argc - 2], envp);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc < 5)
// 		inp_error();
// 	pipex(argc, argv, envp);
// 	return (0);
// }
