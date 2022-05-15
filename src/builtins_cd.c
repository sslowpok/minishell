/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:01:07 by coverand          #+#    #+#             */
/*   Updated: 2022/05/15 20:00:35 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include <string.h>
#include <sys/errno.h>
#include <sys/param.h>

/*
change path1 to path2
*/
void	ft_change_old_dir_envp(char *path, t_llist **envp)
{
	t_llist	*env;

	env = *envp;
	while (env)
	{
		if (!(ft_strcmp("OLDPWD", env->key)))
		{
			free(env->value);
			env->value = ft_strdup(path);
			return ;
		}
		env = env->next;
	}
}

void	ft_change_new_dir_envp(char *path, t_llist **envp)
{
	t_llist	*env;

	env = *envp;
	while (env)
	{
		if (!(ft_strcmp("PWD", env->key)))
		{
			free(env->value);
			env->value = ft_strdup(path);
			return ;
		}
		env = env->next;
	}
}

void	ft_no_arguments(t_llist *envp)
{
	char	*dir;
	
	dir = ft_get_value_envp(&envp, "HOME");
//	ft_change_dir_envp("OLDPWD", "PWD", &envp);
	global.last_return = chdir(dir);
	if (global.last_return)
	{
		if (errno)
		{
			printf("cd: %s: %s", strerror(errno), dir);
			return ;
		}
	}
//		ft_change_dir_envp("PWD", "HOME", &envp);
}

/*
If no arguments given:
1) go to HOME
2) Change PWD to HOME
3) Change OLDPWD to previos PWD
*/
void	ft_cd(char **args, t_llist *envp)
{
//	char	*dir;
	char	old_path[MAXPATHLEN];
	char	new_path[MAXPATHLEN];
	//char	*tmp;

	getcwd(old_path, MAXPATHLEN);
	if (!args[1])
		ft_no_arguments(envp);
	else
		printf("Can't handle it yet!\n");
	getcwd(new_path, MAXPATHLEN);
	ft_change_old_dir_envp(old_path, &envp);
	ft_change_new_dir_envp(new_path, &envp);
}
