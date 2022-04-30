/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:42:57 by coverand          #+#    #+#             */
/*   Updated: 2022/04/30 16:53:37 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define MINISHELL  "minishell: "
/*Defining parser error messages*/
# define PARSER_ERR_IN      "syntax error near unexpected token `>'"
# define PARSER_ERR_OUT     "syntax error near unexpected token `<'"
# define PARSER_ERR_IN_APP  "syntax error near unexpected token `>>'"
# define PARSER_ERR_HEREDOC "syntax error near unexpected token `<<'"
# define PARSER_ERR_PIPE    "syntax error near unexpected token `|'"
# define PARSER_ERR_LAST    "syntax error near unexpected token `newline'"
# define ERR_SINGLE_QUOTES  "unmatched single quotes"
# define ERR_DOUBLE_QUOTES  "unmatched double quotes"

/*File parser_lexer.c*/
int		ft_lexer(char *line, t_list **lex);

/*File parser_lexemes_to_bp.c*/
int		ft_lexeme_to_bp(t_list **bp, t_list **lexemes);

/*File parser_redir_utils.c*/
int		ft_count_redirects(t_list **cmd);
int		ft_is_redirect(char	*str);

/*File parser_utils1.c*/
char	*ft_pop_front(t_list **head);
void	ft_delete_list(t_list **head);

/*File parser_block_process_clear.c*/
void	ft_free_struct_bp(t_block_process *bp);
void	ft_free_block_process(t_list **head);

#endif
