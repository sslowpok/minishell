/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:05:48 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 11:33:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**paths_fill(char **paths)
{
	int		i;
	char	*tmp;

	if (!paths)
		strerror(errno);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			strerror(errno);
		free(paths[i]);
		paths[i] = ft_strdup(tmp);
		if (!paths[i] || !tmp)
			strerror(errno);
		free(tmp);
		i++;
	}
	return (paths);
}

char	**get_paths(void)
{
	char	**paths;
	t_llist	*list;

	list = global.envp_list;
	while (list)
	{
		if (ft_strcmp(list->key, "PATH") == 0)
		{
			paths = paths_fill(ft_split(list->value, ':'));
			return (paths);
		}
		list = list->next;
	}
	return (0);
}

int	ft_paths_len(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strdup(cmd_flags[0]);
	if (!cmd)
		strerror(errno);
	if (!access(cmd, F_OK))
		return (cmd);
	else
	{
		free(cmd);
		while (paths[i])
		{
			
			cmd = ft_strjoin(paths[i], cmd_flags[0]);
			if (!access(cmd, F_OK))
				break ;
			free(cmd);
			if (i == ft_paths_len(paths) - 1)
			{
				printf("💀 > command not found: %s\n", cmd_flags[0]);
				global.last_return = 1;
				exit (1);
			}
			
			i++;
		}
	}
	return (cmd);
}
