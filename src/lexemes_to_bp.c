/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexemes_to_bp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:39:49 by coverand          #+#    #+#             */
/*   Updated: 2022/04/28 15:45:26 by coverand         ###   ########.fr       */
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
	t_list	*list_lex;
	t_list	*cmd;

	list_lex = *lexemes;
	cmd = NULL;
	while (list_lex)
	{
	//	printf("Debug\n");
		if (!ft_strncmp((const char *)list_lex->content, "|", 1))
		{
			//do smth - add commands to struct O_O
			while (cmd)
			{
				printf("%s\n", (char *)cmd->content);
				cmd = cmd->next;
			}
			exit(EXIT_SUCCESS);
		}
		else //add element to cmd and then add this cmd to bp
		{
			if (!cmd)
				cmd = ft_lstnew((void *)ft_pop_front(&list_lex));
			else
				ft_lstadd_back(&cmd, ft_lstnew((void *)ft_pop_front(&list_lex)));
		}
	}
	return (0);
}
