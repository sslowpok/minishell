/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:04:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:32:01 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int code)
{
	if (code == SIGINT)
		ft_putstr_fd("\b\b\n💀 > ", 2);
	else if (code == SIGQUIT)
		ft_putstr_fd("\b\b", 1);
}
