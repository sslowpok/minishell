/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:42:57 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:43:02 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "envp_parser.h"

# define MINISHELL  "minishell: "
/*Defining parser error messages*/
# define PARSER_ERR_IN      "syntax error near unexpected token `>'\n"
# define PARSER_ERR_OUT     "syntax error near unexpected token `<'\n"
# define PARSER_ERR_IN_APP  "syntax error near unexpected token `>>'\n"
# define PARSER_ERR_HEREDOC "syntax error near unexpected token `<<'\n"
# define PARSER_ERR_PIPE    "syntax error near unexpected token `|'\n"
# define PARSER_ERR_LAST    "syntax error near unexpected token `newline'\n"
# define ERR_SINGLE_QUOTES  "unmatched single quotes\n"
# define ERR_DOUBLE_QUOTES  "unmatched double quotes\n"

char	*ft_strjoin_mod(char const *s1, char ch);

int		ft_lexer(char *line, t_list **lex);

int		ft_lexeme_to_bp(t_list **bp, t_list **lexemes, t_llist *envp);

int		ft_count_redirects(t_list **cmd);
int		ft_is_redirect(char	*str);

char	*ft_pop_front(t_list **head);
void	ft_delete_list(t_list **head);
int		ft_isspace(char s);
int		ft_check_quotes(char *line);
char	*ft_strjoin_mod(char const *s1, char ch);

void	ft_free_struct_bp(t_block_process *bp);
void	ft_free_block_process(t_list **head);

int		ft_print_parse_error(char *msg);
int		ft_check_pipe_error(t_list *lexemes);
int		ft_check_redirect_error(t_list **cmd);
int		ft_delete_quotes(t_list **cmd, t_llist *envp);
char	*ft_deal_single_quote(char *str, int *j, char *to_copy);

#endif
