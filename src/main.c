/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:10:57 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:37:20 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/envp_parser.h"
#include "../includes/builtins.h"

char	*ft_readline(void)
{
	char	*line_read;

	line_read = readline("💀 > ");
	if (!line_read)
	{
		printf("\033[A\n💀 > exit\n");
		exit(0);
		signal(SIGINT, handler);
	}
	if (!line_read)
		exit(EXIT_FAILURE);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

int	ft_infinite_loop(char *line, __unused t_info *info)
{
	t_list	*lexems;
	t_list	*bp;

	while (1)
	{
		line = ft_readline();
		if (ft_lexer(line, &lexems))
			return (1);
		ft_lexeme_to_bp(&bp, &lexems, g_global.envp_list);
		g_global.last_return = new_executor(bp);
		ft_free_block_process(&bp);
		free(line);
	}
	return (0);
}

int	main(int argc, char __unused **argv, char **envp)
{
	t_info		info;
	char		*line;

	if (argc != 1)
		return (1);
	g_global.last_return = 0;
	g_global.local_envp = envp;
	g_global.envp_list = ft_init_envp_list(envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	ft_infinite_loop(line, &info);
	return (0);
}
