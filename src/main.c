/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:10:57 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/12 17:19:48 by sslowpok         ###   ########.fr       */
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
int	main(int argc, char __unused **argv, char **envp)
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
	/*char	*lol = ft_get_value_envp(&info.envp_list, "USER");
	if (!lol)
		printf("No\n");
	else
		printf("%s\n", lol);
	free(lol);*/
	/*ft_remove_elem_envp(&info.envp_list, "USER");
	ft_remove_elem_envp(&info.envp_list, "SHLVL");
	while (info.envp_list)
	{
		printf("%s=%s\n", info.envp_list->key, info.envp_list->value);
		info.envp_list = info.envp_list->next;
	}*/
	while (1)
	{
		line = ft_readline();
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_lexer(line, &lexems))
			return (1);
		/*t_list *lex = lexems;
		while (lex)
		{
			printf("%s\n", (char *)lex->content);
			lex = lex->next;
		}*/
		ft_lexeme_to_bp(&bp, &lexems, info.envp_list);

// t_list	*tmp = bp;
// 		printf("size: %i\n", ft_lstsize(tmp));
// 		while (tmp)
// 		{
// 			int	i;
// 			i = 0;
// 			t_block_process	*block = (t_block_process *)tmp->content;
// 			while (block->argv[i])
// 			{
// 				printf("%i) %s\n", i, block->argv[i]);
// 				i++;
// 			}
// 			// while (i < block->files_count)
// 			// {
// 			// 	printf("redir: %i, file: %s\n", block->files[i].redirect_type, block->files[i].file_name);
// 			// 	i++;
// 			// }
// 			tmp = tmp->next;
// 		}
		
		// ls -la | grep "lol"
// 			имеем bp - тип t_list, content - структуры t_block_process
// 		typedef struct s_block_process
// {
// 	char		**argv; // "ls" "-la" ; "grep" "lol"
// 	t_file_info	*files;	// {0, filename}
// 	int			files_count;	// мб кол-во редиректов
// 	int			argc;	// хз че это
// }	t_block_process;

	t_block_process	*block;

	block = (t_block_process *)bp->content;

	// printf("argv[0] = %s\n", block->argv[0]);
	// printf("argv[1] = %s\n", block->argv[1]);

	// char	*a[3];
	// a[0] = "ls";
	// a[1] = "-l";
	// a[2] = "\0";

	
	global.local_envp = envp;
// local envp можно сделать листом, Диана говорит, с ним удобнее работать :)


	executor(bp);
// printf("was here\n");
		
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
