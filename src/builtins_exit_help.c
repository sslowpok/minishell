/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:36:07 by coverand          #+#    #+#             */
/*   Updated: 2022/05/18 16:44:52 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
	while (ft_isspace(str[i]))
		i++;
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

void	ft_handle_lli(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 1);
	ft_putstr_fd(&(str[i]), 1);
	ft_putendl_fd(": numeric argument required", 1);
	exit(255);
}

long long	ft_get_num(char *str)
{
	unsigned long long	num;
	unsigned long long	meow;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	num = 0;
	meow = LLI_PLUS;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i++] - '0');
		if (num > (meow + 1) && sign == -1)
			ft_handle_lli(str);
		if (num > meow)
			ft_handle_lli(str);
	}
	return (sign * num);
}
