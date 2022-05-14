/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:41:25 by coverand          #+#    #+#             */
/*   Updated: 2022/05/14 18:15:52 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
/*
The echo utility writes any specified operands, separated by single blank
	 (` ') characters and followed by a newline (`\n') character, to the stan-
	 dard output.
*/
int	ft_echo_help(char **args, int *j)
{
	int	i;

	i = *j;
	while (args[i])
	{
		if (printf("%s", args[i++]) < 0)
			return (1);
		if (args[i])
			if (printf(" ") < 0)
				return (1);
	}
	*j = i;
	global.last_return = 0;
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	global.last_return = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		flag = 1;
		i++;
	}
	if (ft_echo_help(args, &i))
		return ;
	if (flag == 1 && i > 2)
	{
		if (printf("%%") < 0)
			return ;
	}
	else if (flag != 1)
	{
		if (printf("\n") < 0)
			return ;
	}
	global.last_return = 0;
}
