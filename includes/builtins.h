/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:25:17 by coverand          #+#    #+#             */
/*   Updated: 2022/05/18 16:04:16 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "envp_parser.h"

# define LLI_PLUS   (unsigned long long)9223372036854775807
# define LLI_MINUS  9223372036854775808

void	ft_echo(char **args);
void	ft_env(char **args, t_llist *envp);
void	ft_pwd(char **args, t_llist *envp);
void	ft_cd(char **args, t_llist *envp);
void	ft_exit(char **args, t_llist *envp);
#endif