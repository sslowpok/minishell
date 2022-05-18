/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:54:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/18 18:00:56 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/envp_parser.h"

void	ft_unset(t_block_process *block, __unused t_llist *list)
{
	// not done
	ft_remove_elem_envp(&global.envp_list, block->argv[1]);
	global.last_return = 0;
}