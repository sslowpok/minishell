/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:01:07 by coverand          #+#    #+#             */
/*   Updated: 2022/05/15 17:02:24 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*
change path1 to path2
*/
void	ft_change_dir_envp(char *path1, char *path2, t_llist **envp)
{
	t_llist	*env;
	char	*val;

	env = *envp;
	val = ft_get_value_envp(&env, path2);
	while (env)
	{
		if (!(ft_strcmp(path1, env->key)))
		{
			free(env->value);
			env->value = val;
			return ;
		}
		env = env->next;
	}
}

/*
If no arguments given:
1) go to HOME
2) Change PWD to HOME
3) Change OLDPWD to previos PWD
*/
void	ft_cd(char **args, t_llist *envp)
{
	char	*dir;
	//char	*tmp;

	if (!args[1])
	{
		dir = ft_get_value_envp(&envp, "HOME");
		ft_change_dir_envp("OLDPWD", "PWD", &envp);
		chdir(dir);
		ft_change_dir_envp("PWD", "HOME", &envp);
	}
	else
		printf("Can't handle it yet!\n");
}
