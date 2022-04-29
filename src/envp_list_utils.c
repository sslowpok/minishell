/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:54:49 by coverand          #+#    #+#             */
/*   Updated: 2022/04/29 17:43:55 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/envp_parser.h"

/*Function that deletes data with specified key element from envp_list*/
/*
Iterative Method:
Find the previous node of the node to be deleted.
Change the next of the previous node.
Free memory for the node to be deleted.
*/
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
