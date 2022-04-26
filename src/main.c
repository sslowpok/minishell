/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:10:57 by sslowpok          #+#    #+#             */
/*   Updated: 2022/04/26 20:19:04 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_res_words(t_info *info)
{
	info->reserved_words[0] = "echo";
	info->reserved_words[1] = "cd";
	info->reserved_words[2] = "pwd";
	info->reserved_words[3] = "export";
	info->reserved_words[4] = "unset";
	info->reserved_words[5] = "env";
	info->reserved_words[6] = "exit";
}

void	init_info(t_info *info, char **envp)
{
	init_res_words(info);
	info->envp = envp;
	info->envp_f = 0;
	info->exit_f = 0;
	info->status = 0;
}

/*
Source: https://web.mit.edu/gnu/doc/html/rlman_2.html
*/
/* 
1) Get a line from the user. 
2) If the line has any text in it, save it on the history.
3) Return line.
*/
char	*ft_readline(void)
{
	char	*line_read;

	line_read = readline("💀 > ");
	if (!line_read)
		exit(EXIT_FAILURE);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

int	main(int argc, char __unused **argv, char __unused **envp)
{
	t_info	info;
	char	*line;

	if (argc != 1)
	{
		return (1);
	}
	init_info(&info, envp);
	while (1)
	{
		line = ft_readline();
		if (ft_lexer(line))
			return (1);
		free(line);
	}
	return (0);
}
