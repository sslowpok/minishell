/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:14:11 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:35:17 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_env(char **args)
{
	t_llist	*envp;

	envp = g_global.envp_list;
	if (args[1])
	{
		printf("env usage: env\n");
		g_global.last_return = 127;
		return ;
	}
	while (envp)
	{
		ft_putstr_fd(envp->key, g_global.builtin_fd);
		ft_putstr_fd("=", g_global.builtin_fd);
		ft_putendl_fd(envp->value, g_global.builtin_fd);
		envp = envp->next;
	}
	g_global.last_return = 0;
}
