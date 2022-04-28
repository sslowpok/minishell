/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:42:57 by coverand          #+#    #+#             */
/*   Updated: 2022/04/28 19:05:09 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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

#endif
