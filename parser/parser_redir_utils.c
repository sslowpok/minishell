/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:02:24 by coverand          #+#    #+#             */
/*   Updated: 2022/04/28 19:02:41 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	ft_count_redirects(t_list **cmd)
{
	int		count;
	t_list	*tmp;

	tmp = *cmd;
	count = 0;
	while (tmp)
	{
		if (!ft_strncmp((const char *)tmp->content, ">", 2))
			count++;
		if (!ft_strncmp((const char *)tmp->content, "<", 2))
			count++;
		if (!ft_strncmp((const char *)tmp->content, ">>", 3))
			count++;
		if (!ft_strncmp((const char *)tmp->content, "<<", 3))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
>(0) >>(1) <(2) <<(3)
*/
int	ft_is_redirect(char	*str)
{
	if (!ft_strncmp(str, ">", 2))
		return (0);
	if (!ft_strncmp(str, ">>", 3))
		return (1);
	if (!ft_strncmp(str, "<", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (3);
	return (-1);
}
