/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:25:17 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 14:56:18 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "parser.h"
# include "envp_parser.h"

# define LLI_PLUS   9223372036854775807

void		ft_echo(char **args);
void		ft_env(char **args, t_llist *envp);
void		ft_pwd(char **args, t_llist *envp);
void		ft_cd(char **args, t_llist *envp);
void		ft_exit(char **args, t_llist *envp);
//int			ft_isspace(char s);
int			ft_get_args_count(char **args);
int			ft_check_digit(char *str);
void		ft_handle_lli(char *str);
long long	ft_get_num(char *str);
void		ft_change_old_dir_envp(char *path, t_llist **envp);
void		ft_change_new_dir_envp(char *path, t_llist **envp);

#endif