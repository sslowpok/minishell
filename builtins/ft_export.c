/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:45:26 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:49:19 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

void	ft_export(t_block_process *block)
{
	char	**tmp;
	t_llist	*ptr;

	if (block->argv[1])
	{
		ptr = g_global.envp_list;
		tmp = ft_split(block->argv[1], '=');
		if (!tmp)
			strerror(errno);
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_llist));
		if (!ptr->next)
			strerror(errno);
		ptr->next->key = tmp[0];
		ptr->next->value = tmp[1];
		ptr->next->next = NULL;
	}
	else
		ft_env(block->argv);
}
