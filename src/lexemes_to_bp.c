/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexemes_to_bp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:39:49 by coverand          #+#    #+#             */
/*   Updated: 2022/04/28 18:00:13 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"


char	*ft_pop_front(t_list **head)
{
	t_list	*prev;
	char	*val;

	prev = NULL;
	if (head == NULL)
		return (NULL);
	prev = (*head);
	val = (char *)prev->content;
	(*head) = (*head)->next;
	free(prev);
	return (val);
}

int	ft_count_redirects(t_list **cmd)
{
	int		count;
	t_list	*tmp;

	tmp = *cmd;
	count = 0;
	while (tmp)
	{
		if (!ft_strncmp((const char *)tmp->content, ">", 2))
			count++;
		if (!ft_strncmp((const char *)tmp->content, "<", 2))
			count++;
		if (!ft_strncmp((const char *)tmp->content, ">>", 3))
			count++;
		if (!ft_strncmp((const char *)tmp->content, "<<", 3))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
>(0) >>(1) <(2) <<(3)
*/
int	ft_is_redirect(char	*str)
{
	if (!ft_strncmp(str, ">", 2))
		return (0);
	if (!ft_strncmp(str, ">>", 3))
		return (1);
	if (!ft_strncmp(str, "<", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (3);
	return (-1);
}

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

void	ft_delete_list(t_list **head)
{
	t_list*	prev;
	
	prev = NULL;
	while ((*head)->next)
	{
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}
	free(*head);
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
	ft_delete_list(cmd);
	return (block);
}

/*
for lexeme in lexemes:														//	функция в которой мы трансформируем список лексем
	if (lexeme != '|')														//	в структуру блока процессов
		lexemes_for_block_process.push_back(lexeme)							//	заполняем список блока процсса лексемами
	else:																	//
		block_processes.push_back(create(lexemes_for_block_process));		//иначе переходим в функцию трансформации списка (create(list<lexeme>))лексем в block_process и пушим в с конец списка блоков процесса
		lexemes_for_block_process = empty;									//и очищаем список
*/
int	ft_lexeme_to_bp(t_list __unused **bp, t_list **lexemes)
{
	t_list	*lex;
	t_list	*cmd;

	lex = *lexemes;
	cmd = NULL;
	while (lex)
	{
		if (!ft_strncmp((const char *)lex->content, "|", 2))
		{
			ft_pop_front(&lex);
			if (!(*bp))
				*bp = ft_lstnew((void *)ft_create_bp(&cmd));
			else
				ft_lstadd_back(bp, ft_lstnew((void *)ft_create_bp(&cmd)));
		}
		else
		{
			if (!cmd)
				cmd = ft_lstnew((void *)ft_pop_front(&lex));
			else
				ft_lstadd_back(&cmd, ft_lstnew((void *)ft_pop_front(&lex)));
		}
		t_list	*tmp = *bp;
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
			tmp = tmp->next;
		}
	}
	return (0);
}
