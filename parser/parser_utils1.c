/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:42:00 by coverand          #+#    #+#             */
/*   Updated: 2022/05/13 16:33:03 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
/*
Source: https://learnc.info/adt/linked_list.html
*/
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
Source: https://learnc.info/adt/linked_list.html
*/
void	ft_delete_list(t_list **head)
{
	t_list	*prev;

	prev = NULL;
	while ((*head)->next)
	{
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}
	*head = NULL;
	free(*head);
}

int	ft_isspace(char s)
{
	if (s == ' ' || s == '\t' || s == '\n' || \
s == '\v' || s == '\f' || s == '\r')
		return (1);
	return (0);
}

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
				return (ft_print_parse_error(ERR_DOUBLE_QUOTES));
		}
		if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (!line[i])
				return (ft_print_parse_error(ERR_SINGLE_QUOTES));
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin_mod(char const *s1, char ch)
{
	int		len1;
	char	*str;
	int		i;

	i = 0;
	len1 = ft_strlen(s1);
	str = malloc(sizeof(*str) * (len1 + 1) + 1);
	if (str == 0)
		return (0);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = ch;
	i++;
	str[i] = '\0';
	return (str);
}
