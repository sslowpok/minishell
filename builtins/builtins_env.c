/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:14:11 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:02:44 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*
If no utility is specified, 
env prints out the names and values of the variables in the
environment, with one name/value pair per line.
*/

/*
The env utility exits 0 on success, and >0 if an error occurs.
An exit status of 126 indicates that utility was found, 
but could not be executed.
An exit status of 127 indicates that utility could not be found.
*/

void	ft_env(char **args)
{
	t_llist	*envp;

	envp = global.envp_list;
	if (args[1])
	{
		printf("env usage: env\n");
		global.last_return = 127;
		return ;
	}
	while (envp)
	{
		ft_putstr_fd(envp->key, global.builtin_fd);
		ft_putstr_fd("=", global.builtin_fd);
		ft_putendl_fd(envp->value, global.builtin_fd);
		envp = envp->next;
	}
	global.last_return = 0;
}
