/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:21:08 by coverand          #+#    #+#             */
/*   Updated: 2022/04/26 19:53:23 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
34 - Double-Quotes
39 - Single-Quotes
*/
int	ft_check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			i++;
			while (line[i] && line[i] != 34)
				i++;
			if (!line[i])
				return (1);
		}
		if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

/*
This help function prevents splitting inside quotes.
*/
void	ft_strtok_help(char **stock)
{
	if (**stock == '\'')
	{
		(*stock)++;
		while (**stock != '\'')
			(*stock)++;
	}
	if (**stock == '"')
	{
		(*stock)++;
		while (**stock != '"')
			(*stock)++;
	}
}

/*
https://opensource.apple.com/source/Libc/Libc-167/string.subproj/
strsep.c.auto.html
*/
/*
1) If str exists, copy its content to stock.
ptr = stock.
2) Iterate throught stock.
- if given string has quotes, function ft_strtok_help skips them 
  (we do not need split content inside quotes)
- if symbol in string is equal to given delimeter => replace delimeter with '\0'
3) Return pointer to the first element in stock that is not equal to delimeter.
*/
char	*ft_strtok(char *str, const char delim)
{
	static char		*stock = NULL;
	char			*ptr;
	int				flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (flg == 0 && *stock != delim)
		{
			flg = 1;
			ptr = stock;
		}
		ft_strtok_help(&stock);
		if (flg == 1 && *stock == delim)
		{
			*stock = '\0';
			stock++;
			break ;
		}
		stock++;
	}
	return (ptr);
}

/*
1) Check that each outer open quote has corresponding closing quote.
2) Get tokens (lexems).
*/
int	ft_lexer(char *line)
{
	char	*token;

	if (ft_check_quotes(line))
		return (1);
	token = ft_strtok(line, ' ');
	while (token != NULL)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, ' ');
	}
	return (0);
}
