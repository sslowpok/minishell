/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:10:57 by sslowpok          #+#    #+#             */
/*   Updated: 2022/04/29 16:49:22 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/envp_parser.h"

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
	info->envp_list = ft_init_envp_list(envp);
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

/* bp - list with block_processes. 
Each element of bp has structure t_block_process as content*/
int	main(int argc, char __unused **argv, char __unused **envp)
{
	t_info	info;
	char	*line;
	t_list	*lexems;
	t_list	*bp;

	bp = NULL;
	lexems = NULL;
	if (argc != 1)
	{
		return (1);
	}
	init_info(&info, envp);
	while (info.envp_list)
	{
		printf("%s=%s\n", info.envp_list->key, info.envp_list->value);
		info.envp_list = info.envp_list->next;
	}
	while (1)
	{
		line = ft_readline();
		if (ft_lexer(line, &lexems))
			return (1);
		ft_lexeme_to_bp(&bp, &lexems);
		ft_free_block_process(&bp);
		free(line);
	}
	return (0);
}

/*t_list	*tmp = bp;
		printf("size: %i\n", ft_lstsize(tmp));
		while (tmp)
		{
			int	i;
			i = 0;
			t_block_process	*block = (t_block_process *)tmp->content;
			while (block->argv[i])
			{
				printf("%i) %s\n", i, block->argv[i]);
				i++;
			}
			while (i < block->files_count)
			{
				printf("redir: %i, file: %s\n", block->files[i].redirect_type, block->files[i].file_name);
				i++;
			}
			tmp = tmp->next;
		}*/
