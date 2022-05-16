/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:54:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/16 17:13:09 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

void	ft_unset(t_block_process *block, t_llist *list)
{
	// not done
	printf("to delete: %s\n", block->argv[1]);
	while (ft_strcmp(list->next->key,block->argv[1]))
	{
		printf("current key: %s\n", list->next->key);
		list = list->next;
	}
	list->next = list->next->next;
	global.last_return = 0;
}