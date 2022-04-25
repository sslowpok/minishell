/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:49:51 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:45 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include "../includes/pipex_bonus.h"

char	*make_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strdup(cmd_flags[0]);
	if (!cmd)
		error(errno, "malloc: ");
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
			i++;
		}
	}
	return (cmd);
}

void	execute_cmd(char *arg, char **envp)
{
	char	**paths;
	char	**cmd_flags;
	char	*cmd;

	paths = get_paths(envp);
	if (!paths)
		error(errno, "Malloc: ");
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		error(errno, "Malloc: ");
	cmd = make_cmd(paths, cmd_flags);
	if (!cmd)
		error(errno, "Malloc: ");
	if (execve(cmd, cmd_flags, envp) < 0)
		error(-1, cmd_flags[0]);
	total_free(paths);
	total_free(cmd_flags);
}
