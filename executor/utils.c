/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:12:47 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:27:08 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	total_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	init_child(t_child *child, t_list *bp)
{
	child->i = -1;
	child->current = 0;
	child->fd[0][0] = -1;
	child->fd[0][1] = -1;
	child->fd[1][0] = -1;
	child->fd[1][1] = -1;
	child->fd_in = 0;
	child->fd_out = 0;
	child->len = ft_lstsize(bp);
}

void	help_executor(t_child *child, t_block_process *block)
{
	child->pid = fork();
	if (child->pid == 0)
		if (child_labour(child, block, child->len) == 1)
			exit (1);
	close(child->fd[1 - child->current][0]);
	close(child->fd[child->current][1]);
	child->current = 1 - child->current;
}
