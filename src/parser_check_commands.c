/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:55:09 by coverand          #+#    #+#             */
/*   Updated: 2022/04/30 18:24:28 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"

/*
Error management:
1) If '>', '>>', '<', '<<' are the last args:
"bash: syntax error near unexpected token `newline'"

2) there is no args b/w redirects: 
bash: syntax error near unexpected token `>'

3) If there is 2 pipes
"bash: syntax error near unexpected token `|'"

4) Just 1 arg - 1 pipe (ex: "| cat")
bash: syntax error near unexpected token `|'

4) Unclosed quotes messages (bash waits closing quotes, but we should not  interpret unclosed quotes):
bash: syntax error near unexpected token: '"'
bash: syntax error near unexpected token '"

5) export ARG = "5" -> There cannot be any space on either side of the equal sign.
bash: export: `=': not a valid identifier
bash: export: `5': not a valid identifier
*/

int	ft_print_parse_error(char __unused *msg)
{
	printf(MINISHELL);
	printf("%s", msg);
	return (1);
}

/*
Errors:
1) if lex is '|' and there is no lex->next
2) if lex is '|' and lex->next is '|'
3) if lex is redirect and lex->next is '|'
4) if lex is '|' and lex->next is redirect
*/
int	ft_check_pipe(t_list *lexemes)
{
	if (!ft_strcmp((const char *)lexemes->content, "|") && !lexemes->next)
		return (ft_print_parse_error(PARSER_ERR_PIPE));
	if (lexemes->next)
	{
		if (ft_strcmp((const char *)lexemes->content, "|") == 0 && \
		ft_strcmp((const char *)lexemes->next->content, "|") == 0)
			return (ft_print_parse_error(PARSER_ERR_PIPE));
		if (ft_is_redirect((char *)lexemes->content) != -1 && \
		!ft_strcmp((const char *)lexemes->next->content, "|"))
			return (ft_print_parse_error(PARSER_ERR_PIPE));
		if (ft_is_redirect((char *)lexemes->next->content) != -1 && \
		!ft_strcmp((const char *)lexemes->content, "|"))
			return (ft_print_parse_error(PARSER_ERR_PIPE));
	}
	return (0);
}