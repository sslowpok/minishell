/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:54:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:36:23 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/envp_parser.h"

void	ft_unset(t_block_process *block)
{
	ft_remove_elem_envp(&g_global.envp_list, block->argv[1]);
	g_global.last_return = 0;
}
