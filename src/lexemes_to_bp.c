/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexemes_to_bp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:39:49 by coverand          #+#    #+#             */
/*   Updated: 2022/04/27 14:06:33 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
for lexeme in lexemes:														//	функция в которой мы трансформируем список лексем
	if (lexeme != '|')														//	в структуру блока процессов
		lexemes_for_block_process.push_back(lexeme)							//	заполняем список блока процсса лексемами
	else:																	//
		block_processes.push_back(create(lexemes_for_block_process));		//иначе переходим в функцию трансформации списка (create(list<lexeme>))лексем в block_process и пушим в с конец списка блоков процесса
		lexemes_for_block_process = empty;									//и очищаем список
*/
int	ft_lexeme_to_bp(t_list **bp)
{
	return (0);
}
