/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:04:20 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 11:35:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd("\b\b\n💀 >", 2);
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//if (!g_sig.pid)
		//	rl_redisplay();
	}
	else if (code == SIGQUIT)
	{
		ft_putstr_fd("\b\b", 1);
		//rl_on_new_line();
		//if (!g_sig.pid)
		//	rl_redisplay();
		//else
		//{
			ft_putendl_fd("Quit: 3", 1);
			//g_sig.ex_code = 131;
		//}
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
