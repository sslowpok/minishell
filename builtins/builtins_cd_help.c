/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:55:11 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 18:29:00 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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

/*
change PWD value in envp
*/
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