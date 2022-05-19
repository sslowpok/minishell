/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:04:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/19 17:04:57 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int code)
{
	if (code == SIGINT)
	{
		write(1, "\n💀 > ", 8);
		signal(SIGINT, handler);
	}
		// write(1, "\n💀 > ", 8);
	// if (code == SIGQUIT)
	// {
	// 	printf("\033[A\n💀 > exit\n");
	// 	exit(0);
	// }
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
}
