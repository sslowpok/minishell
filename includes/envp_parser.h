/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:19:12 by coverand          #+#    #+#             */
/*   Updated: 2022/04/29 17:16:20 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_PARSER_H
# define ENVP_PARSER_H

# include "minishell.h"

/*File envp_parser_utils.c*/
t_llist	*ft_init_envp_list(char **envp);
t_llist	*ft_lstnew_envp(char *key, char *value);
void	ft_lstadd_back_envp(t_llist **lst, t_llist *new);

void	ft_remove_elem_envp(t_llist **envp_list, char *key);

#endif
