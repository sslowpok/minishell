/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_deal_quotes2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:39:51 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 19:41:41 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/builtins.h"

char	*ft_deal_single_quote(char *str, int *j, char *to_copy)
{
	int		i;

	i = *j;
	i++;
	while (to_copy[i] != 39)
	{
		str = ft_strjoin_mod(str, to_copy[i]);
		i++;
	}
	i++;
	*j = i;
	return (str);
}
