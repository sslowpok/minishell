/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:09:54 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 18:36:00 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/minishell.h"

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
	r_out_builtin(block);
	builtin_execute(block);
	return (0);
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
	if (!ft_strcmp(block->argv[0], "cd"))
		return (1);
	return (0);
}

void	builtin_execute(t_block_process *block)
{
	if (!ft_strcmp(block->argv[0], "env"))
		ft_env(block->argv);
	if (!ft_strcmp(block->argv[0], "unset"))
		ft_unset(block);
	if (!ft_strcmp(block->argv[0], "echo"))
		ft_echo(block->argv);
	if (!ft_strcmp(block->argv[0], "pwd"))
		ft_pwd(block->argv, global.envp_list);
	if (!ft_strcmp(block->argv[0], "export"))
		ft_export(block);
	if (!ft_strcmp(block->argv[0], "exit"))
		ft_exit(block->argv, global.envp_list);
	if (!ft_strcmp(block->argv[0], "cd"))
		ft_cd(block->argv, global.envp_list);
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
