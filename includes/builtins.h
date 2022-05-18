/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:25:17 by coverand          #+#    #+#             */
/*   Updated: 2022/05/18 17:50:17 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "parser.h"

# define LLI_PLUS   9223372036854775807

void	ft_echo(char **args);
void	ft_env(char **args);
void	ft_pwd(char **args, t_llist *envp);
void	ft_unset(t_block_process *block, t_llist *list);
void	ft_export(t_block_process *block);
void		ft_exit(char **args, t_llist *envp);
//int			ft_isspace(char s);
int			ft_get_args_count(char **args);
int			ft_check_digit(char *str);
void		ft_handle_lli(char *str);
long long	ft_get_num(char *str);

#endif