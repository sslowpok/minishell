/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_block_process_clear.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:49:22 by coverand          #+#    #+#             */
/*   Updated: 2022/04/28 19:49:57 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_struct_bp(t_block_process *bp)
{
	int	i;

	i = 0;
	while (bp->argv[i])
	{
		free(bp->argv[i]);
		i++;
	}
	i = 0;
	while (i < bp->files_count)
	{
		free(bp->files->file_name);
		i++;
	}
	free(bp->files);
}

void	ft_free_block_process(t_list **head)
{
	t_list	*prev;

	prev = NULL;
	while ((*head)->next)
	{
		prev = (*head);
		ft_free_struct_bp((t_block_process *)prev->content);
		(*head) = (*head)->next;
		free(prev);
	}
	*head = NULL;
	free(*head);
	*head = NULL;
}
