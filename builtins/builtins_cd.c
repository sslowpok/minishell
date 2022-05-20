/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:01:07 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:34:33 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include <string.h>
#include <sys/errno.h>
#include <sys/param.h>

void	ft_no_arguments(t_llist *envp)
{
	char	*dir;

	dir = ft_get_value_envp(&envp, "HOME");
	g_global.last_return = chdir(dir);
	if (g_global.last_return)
	{
		if (errno)
		{
			printf("cd: %s: %s\n", strerror(errno), dir);
			return ;
		}
	}
}

void	ft_go_to_old_path(t_llist *envp)
{
	char	*dir;

	dir = ft_get_value_envp(&envp, "OLDPWD");
	g_global.last_return = chdir(dir);
	if (g_global.last_return)
	{
		if (errno)
		{
			printf("cd: %s: %s\n", strerror(errno), dir);
			return ;
		}
	}
}

void	ft_go_to_path(char *str)
{
	char	*dir;

	dir = ft_strdup(str);
	g_global.last_return = chdir(dir);
	if (g_global.last_return)
	{
		g_global.last_return = 1;
		if (errno)
		{
			printf("cd: %s: %s\n", strerror(errno), dir);
			return ;
		}
	}
}

void	ft_handle_tilda(t_llist **envp, char **args, char *old_path)
{
	char	*dir;

	if (!ft_strchr(args[1], '/') && ft_strlen(args[1]) > 1)
	{
		chdir(args[1]);
		g_global.last_return = 1;
		if (errno)
			printf("cd: %s: %s\n", strerror(errno), args[1]);
		return ;
	}
	dir = ft_get_value_envp(envp, "HOME");
	chdir(dir);
	free(dir);
	if (ft_strlen(args[1]) == 1)
		return ;
	dir = ft_strchr(args[1], '/');
	dir++;
	if (dir && chdir(dir) && ft_strlen(dir) > 1)
	{
		g_global.last_return = 1;
		if (errno)
			printf("cd: %s: %s/%s\n", strerror(errno), \
			ft_get_value_envp(envp, "HOME"), dir);
		chdir(old_path);
	}
}

void	ft_cd(char **args, t_llist *envp)
{
	char	old_path[MAXPATHLEN];
	char	new_path[MAXPATHLEN];

	g_global.last_return = 0;
	getcwd(old_path, MAXPATHLEN);
	if (!args[1])
		ft_no_arguments(g_global.envp_list);
	else
	{
		if (!ft_strcmp("-", args[1]))
			ft_go_to_old_path(g_global.envp_list);
		else if (!ft_strncmp("~", args[1], 1))
			ft_handle_tilda(&g_global.envp_list, args, old_path);
		else
			ft_go_to_path(args[1]);
	}
	getcwd(new_path, MAXPATHLEN);
	ft_change_old_dir_envp(old_path, &envp);
	ft_change_new_dir_envp(new_path, &envp);
}
