/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:42:00 by coverand          #+#    #+#             */
/*   Updated: 2022/04/28 18:48:11 by coverand         ###   ########.fr       */
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
