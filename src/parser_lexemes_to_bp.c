/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexemes_to_bp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:39:49 by coverand          #+#    #+#             */
/*   Updated: 2022/04/30 18:52:23 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	ft_fill_argv_in_bp(char **argv, t_list **cmd, int num)
{
	t_list	*tmp;
	int		i;
	int		redir;

	i = 0;
	tmp = *cmd;
	while (i < num && tmp)
	{
		redir = ft_is_redirect((char *)tmp->content);
		if (redir == -1)
		{
			argv[i] = ft_strdup((char *)tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	argv[i] = NULL;
}

void	ft_fill_redirect_info(t_block_process *block, t_list **cmd)
{
	t_list		*tmp;
	int			i;
	int			redir;
	t_file_info	*files;

	i = 0;
	tmp = *cmd;
	files = malloc(sizeof(t_file_info) * block->files_count);
	if (!files)
		return ;
	while (i < block->files_count && tmp)
	{
		redir = ft_is_redirect((char *)tmp->content);
		if (redir != -1)
		{
			if (tmp->next)
				files[i].file_name = (char *)tmp->next->content;
			files[i].redirect_type = redir;
			i++;
		}
		tmp = tmp->next;
	}
	block->files = files;
}

t_block_process	*ft_create_bp(t_list **cmd)
{
	t_block_process	*block;
	t_list			*tmp;

	tmp = *cmd;
	block = malloc(sizeof(t_block_process));
	if (!block)
		return (NULL);
	block->files_count = ft_count_redirects(cmd);
	block->argc = ft_lstsize(tmp) - block->files_count;
	block->argv = malloc(sizeof(char *) * (block->argc + 1));
	if (!block->argv)
		return (NULL);
	ft_fill_argv_in_bp(block->argv, &tmp, block->argc);
	ft_fill_redirect_info(block, cmd);
	ft_delete_list(cmd);
	return (block);
}

int	ft_create_bp_list(t_list **bp, t_list **cmd)
{
	if (!(*bp) && !(*cmd))
		return (ft_print_parse_error(PARSER_ERR_PIPE));
	if (ft_check_redirect_error(cmd))
		return (1);
	if (!(*bp))
	{
		*bp = ft_lstnew((void *)ft_create_bp(cmd));
		if (!(*bp))
			return (1);
	}
	else
		ft_lstadd_back(bp, ft_lstnew((void *)ft_create_bp(cmd)));
	return (0);
}

int	ft_lexeme_to_bp(t_list **bp, t_list **lexemes)
{
	t_list	*lex;
	t_list	*cmd;

	lex = *lexemes;
	cmd = NULL;
	while (lex)
	{
		// check: if lex is redirect and lex->next is |
		// if lex is | and there is no lex->next
		// if lex is | and lex->next is redirect
		// if lex is | and lex->next is |
	//	printf("%s\n", (const char *)lex->content);
		if (ft_check_pipe_error(lex))
			return (1);
		if (!ft_strncmp((const char *)lex->content, "|", 2))
		{
			ft_pop_front(&lex);
			if (ft_create_bp_list(bp, &cmd))
				return (1);
			/*printf("The end\n");
			exit(EXIT_FAILURE);*/
		}
		else
		{
			if (!cmd)
				cmd = ft_lstnew((void *)ft_pop_front(&lex));
			else
				ft_lstadd_back(&cmd, ft_lstnew((void *)ft_pop_front(&lex)));
			if (!lex)
			{
				if (ft_create_bp_list(bp, &cmd))
					return (1);
			}
		}
	}
	return (0);
}
