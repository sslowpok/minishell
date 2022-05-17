/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:54:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/17 17:56:59 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

void	ft_unset(t_block_process *block, t_llist *list)
{
	// not done
	while (ft_strcmp(list->next->key,block->argv[1]))
	{
		list = list->next;
	}
	list->next = list->next->next;
	global.last_return = 0;
}