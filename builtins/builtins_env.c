/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:14:11 by coverand          #+#    #+#             */
/*   Updated: 2022/05/16 14:42:14 by sslowpok         ###   ########.fr       */
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

void	ft_env(char **args, t_llist *envp)
{
	if (args[1])
	{
		printf("env usage: env\n");
		global.last_return = 127;
		return ;
	}
	while (envp)
	{
		if (printf("%s=%s\n", envp->key, envp->value) < 0)
		{
			global.last_return = 1;
			return ;
		}
		envp = envp->next;
	}
	global.last_return = 0;
}
