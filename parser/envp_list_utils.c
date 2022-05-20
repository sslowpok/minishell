/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:54:49 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:43:17 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/envp_parser.h"

void	ft_remove_elem_envp(t_llist **envp_list, char *key)
{
	t_llist	*curr;
	t_llist	*prev;

	curr = *envp_list;
	prev = NULL;
	if (curr && ft_strcmp((*envp_list)->key, key) == 0)
	{
		*envp_list = curr->next;
		free(curr);
		return ;
	}
	while (curr && ft_strcmp(curr->key, key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	free(curr);
}

char	*ft_get_value_envp(t_llist **envp_list, char *key)
{
	char	*ans;
	t_llist	*tmp;

	ans = NULL;
	tmp = *envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			ans = ft_strdup(tmp->value);
			return (ans);
		}
		tmp = tmp->next;
	}
	return (ans);
}
