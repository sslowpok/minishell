/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:25:17 by coverand          #+#    #+#             */
/*   Updated: 2022/05/15 17:00:54 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "envp_parser.h"

void	ft_echo(char **args);
void	ft_env(char **args, t_llist *envp);
void	ft_pwd(char **args, t_llist *envp);
void	ft_cd(char **args, t_llist *envp);

#endif