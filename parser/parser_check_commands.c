/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:55:09 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:43:48 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minishell.h"

int	ft_print_parse_error(char __unused *msg)
{
	printf(MINISHELL);
	printf("%s", msg);
	return (1);
}

int	ft_check_pipe_error(t_list *lexemes)
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
	}
	return (0);
}

int	ft_check_redirect_error_help(int first, int second)
{
	if (first != -1 && second == 0)
		return (ft_print_parse_error(PARSER_ERR_IN));
	if (first != -1 && second == 1)
		return (ft_print_parse_error(PARSER_ERR_IN_APP));
	if (first != -1 && second == 2)
		return (ft_print_parse_error(PARSER_ERR_OUT));
	if (first != -1 && second == 3)
		return (ft_print_parse_error(PARSER_ERR_HEREDOC));
	return (0);
}

int	ft_check_redirect_error(t_list **cmd)
{
	t_list	*meow;
	int		first;
	int		second;

	meow = *cmd;
	while (meow)
	{
		if (ft_is_redirect((char *)meow->content) != -1 && !meow->next)
			return (ft_print_parse_error(PARSER_ERR_LAST));
		if (meow->next)
		{
			first = ft_is_redirect((char *)meow->content);
			second = ft_is_redirect((char *)meow->next->content);
			if (ft_check_redirect_error_help(first, second))
				return (1);
		}
		meow = meow->next;
	}
	return (0);
}
