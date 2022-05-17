/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:45:26 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/17 18:08:52 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"

// int	ft_llstsize(t_llist *list)
// {
// 	int		i;
// 	t_llist	*tmp;

// 	i = 0;
// 	tmp = list;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// t_llist	*sort_env_list(t_llist *list)
// {
// 	int	i;
// 	int	j;
// 	int	size;

// 	i = 0;
// 	size = ft_llstsize(list);
// 	while (i < size)
// 	{
// 		j = 0;
// 		if ()



// 		i++;
// 	}
// }

// *********************************************
// need to add case for no argv[1] (just export)
// *********************************************
void	ft_export(t_block_process *block)
{
	char	**tmp;
	t_llist	*ptr;

	if (block->argv[1])
	{
		ptr = global.envp_list;
		tmp = ft_split(block->argv[1], '=');
		if (!tmp)
			strerror(errno);
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_llist));
		if (!ptr->next)
			strerror(errno);
		ptr->next->key = tmp[0];
		ptr->next->value = tmp[1];
		ptr->next->next = NULL;
	}
}