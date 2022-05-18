/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:54:44 by coverand          #+#    #+#             */
/*   Updated: 2022/05/18 17:44:32 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

/*
Examples:
1) exit lol
stdout:
exit
bash: exit: lol: numeric argument required
echo $? -> 255
2) exit lol meow
stdout:
exit
bash: exit: lol: numeric argument required
echo $? -> 255
3) exit 5 2
stdout:
exit
bash: exit: too many arguments
No exit =)
echo $? -> 1
4) exit -100
stdout:
exit
echo $? -> 156
5) exit --100
stdout:
exit
bash: exit: --100: numeric argument required
echo $? -> 255
3) exit
stdout:
exit
echo $? -> 1
*/

/*
Source => 
https://stackoverflow.com/questions/11720656/
modulo-operation-with-negative-numbers
*/
int	ft_get_return(long long n)
{
	return ((n % 256 + 256) % 256);
}

void	ft_exit(char **args, t_llist __unused *envp)
{
	int	count;

	count = ft_get_args_count(args);
	if (count == 1)
		exit(1);
	if (count == 2 && !ft_check_digit(args[1]))
		exit(ft_get_return(ft_get_num(args[1])));
	if (ft_check_digit(args[1]))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit(255);
	}
	else if (count > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 1);
		global.last_return = 1;
	}
}