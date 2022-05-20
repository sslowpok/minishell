/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:02:24 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:44:10 by sslowpok         ###   ########.fr       */
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

int	ft_is_redirect(char	*str)
{
	if (!ft_strncmp(str, ">", 2))
		return (4);
	if (!ft_strncmp(str, ">>", 3))
		return (1);
	if (!ft_strncmp(str, "<", 2))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (3);
	return (-1);
}
