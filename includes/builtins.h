/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:25:17 by coverand          #+#    #+#             */
/*   Updated: 2022/05/16 14:48:16 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_echo(char **args);
void	ft_env(char **args, t_llist *envp);
void	ft_pwd(char **args, t_llist *envp);
void	ft_unset(t_block_process *block, t_llist *list);

#endif