/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:12:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/19 17:23:21 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

// если ls + несуществующий файл, не меняется last return

int	execute_cmd(t_block_process *block, __unused pid_t pid)
{
	char	**paths;
	char	*cmd;

	cmd = NULL;
	paths = get_paths();
	if (!paths)
	{
		ft_putendl_fd(": command not found", 2);
		exit (1);
	}
	if (!check_if_builtin(block))
	{
		cmd = make_cmd(paths, block->argv);
		if (!cmd)
			exit (1);
		if (execve(cmd, block->argv, global.local_envp) < 0)
			strerror(errno);
		exit(0);
	}
	total_free(paths);
	return (0);
}

int	child_labour(t_child *child, t_block_process *block, int len)
{
	sig_sig_signal();
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
	if (!ft_strcmp(block->argv[0], block->files[0].file_name))
		return (1);
	return (0);
}

void	new_executor(t_list *bp)
{
	t_child			child;
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
					exit (1);
			close(child.fd[1 - child.current][0]);
			close(child.fd[child.current][1]);
			child.current = 1 - child.current;
		}
		bp = bp->next;
	}
	close(child.fd[1 - child.current][0]);
	wait_child(child.len);
}
