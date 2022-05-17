/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:41:08 by coverand          #+#    #+#             */
/*   Updated: 2022/05/17 17:45:00 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include <sys/param.h>
/*
The pwd utility writes the absolute pathname of the current working directory
to the standard output.
 */
/*
The pwd utility exits 0 on success, and >0 if an error occurs.
*/
/*
The function getwd() is a compatibility routine 
which calls getcwd() with its buf argument and a size of MAXPATHLEN 
(as defined in the include file <sys/param.h>).  
Obviously, buf should be at least MAXPATHLEN bytes in length.
*/

void	ft_pwd(char **args, t_llist __unused *envp)
{
	char	buf[MAXPATHLEN];

	if (args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", global.builtin_fd);
		// printf("pwd: too many arguments\n");
		global.last_return = 1;
		return ;
	}
	if (getcwd(buf, MAXPATHLEN) == NULL)
	{
		global.last_return = 1;
		return ;
	}
	global.last_return = 0;
	// printf("%s\n", buf);
	ft_putendl_fd(buf, global.builtin_fd);
}
