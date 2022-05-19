/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:07:51 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/19 17:09:15 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	r_in(t_block_process *block, t_child *child)
{
	t_file_info	*tmp;
	int			i;
	
	i = 0;
	tmp = block->files;
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
