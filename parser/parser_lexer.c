/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:21:08 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 10:52:28 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*ft_is_quote(char *s, char quote, int *j, char *str)
{
	int		i;

	i = *j;
	s = ft_strjoin_mod(s, str[i]);
	i++;
	while (str[i] != quote)
	{
		s = ft_strjoin_mod(s, str[i]);
		i++;
	}
	s = ft_strjoin_mod(s, str[i]);
	i++;
	*j = i;
	return (s);
}

char	*ft_char_is_space(t_list **lexeme, int *j, char *s, char *str)
{
	int		i;

	i = *j;
	if (ft_strlen(s) != 0)
	{
		ft_lstadd_back(lexeme, ft_lstnew((void *)ft_strdup(s)));
		free(s);
		s = ft_strdup("");
	}
	i++;
	while (ft_isspace(str[i]))
		i++;
	*j = i;
	return (s);
}

char	*ft_char_is_spec(t_list **lexeme, int *j, char *s, char *str)
{
	int		i;

	i = *j;
	if (ft_strlen(s) != 0)
	{
		ft_lstadd_back(lexeme, ft_lstnew((void *)ft_strdup(s)));
		free(s);
	}
	s = ft_strdup("");
	s = ft_strjoin_mod(s, str[i++]);
	if (str[i] && str[i] == str[i - 1] && ft_strchr("><", str[i]) != NULL)
		s = ft_strjoin_mod(s, str[i++]);
	ft_lstadd_back(lexeme, ft_lstnew((void *)ft_strdup(s)));
	free(s);
	s = ft_strdup("");
	*j = i;
	return (s);
}

// put str[i] to s till we meet space or char like pipe or redirect
// pipes and redirects are separate lexemes
t_list	*ft_line_to_lexemes(char *str)
{
	t_list	*lex;
	int		i;
	char	*s;

	lex = NULL;
	i = 0;
	s = ft_strdup("");
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			s = ft_is_quote(s, str[i], &i, str);
		if (str[i] && ft_isspace(str[i]))
			s = ft_char_is_space(&lex, &i, s, str);
		if (str[i] && ft_strchr("><|", str[i]) != NULL)
			s = ft_char_is_spec(&lex, &i, s, str);
		if (str[i] && str[i] != 39 && str[i] != 34 && !ft_isspace(str[i]) \
		&& ft_strchr("><|", str[i]) == NULL)
			s = ft_strjoin_mod(s, str[i++]);
	}
	if (s && ft_strlen(s) != 0)
		ft_lstadd_back(&lex, ft_lstnew((void *)ft_strdup(s)));
	free(s);
	s = NULL;
	return (lex);
}

/*
1) Check that each outer open quote has corresponding closing quote.
2) Get tokens (lexems).
*/
int	ft_lexer(char *line, t_list **lex)
{

	if (ft_check_quotes(line))
		return (1);
	*lex = ft_line_to_lexemes(line);
	return (0);
}
