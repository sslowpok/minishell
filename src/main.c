/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:10:57 by sslowpok          #+#    #+#             */
/*   Updated: 2022/04/25 15:39:15 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_res_words(t_info *info)
{
	info->reserved_words[0] = "echo";
	info->reserved_words[1] = "cd";
	info->reserved_words[2] = "pwd";
	info->reserved_words[3] = "export";
	info->reserved_words[4] = "unset";
	info->reserved_words[5] = "env";
	info->reserved_words[6] = "exit";
}

void	init_info(t_info *info, char **envp)
{
	init_res_words(info);
	info->envp = envp;
	info->envp_f = 0;
	info->exit_f = 0;
	info->status = 0;
}


int	main(int argc, char __unused **argv, char __unused **envp)
{
	t_info	info;

	if (argc != 1)
	{
		return (1);
	}
	
	init_info(&info, envp);
	
	return (0);
}