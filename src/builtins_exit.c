/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:54:44 by coverand          #+#    #+#             */
/*   Updated: 2022/05/18 15:27:37 by coverand         ###   ########.fr       */
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

int	ft_get_args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_num(int n)
{
	/*if (n >= 0)
	{
		if (n <= 255)
			return (n);
		return (n % 255);
	}
	if (n <= -1 && n >= -256)
		return (256 + n);*/
	return ((n % 256 + 256) % 256);
}

void	ft_exit(char **args, t_llist __unused *envp)
{
	int	count;

	count = ft_get_args_count(args);

	if (count == 1)
		exit(1);
	if (count == 2)
	{
		//1) check if digit else - get number
		if (ft_check_digit(args[1]))
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(args[1], 1);
			ft_putendl_fd(": numeric argument required", 1);
			exit(255);
		}
		exit(ft_get_num(ft_atoi(args[1])));
	}
}
