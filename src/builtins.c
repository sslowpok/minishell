/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:41:25 by coverand          #+#    #+#             */
/*   Updated: 2022/05/14 16:12:45 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
The echo utility writes any specified operands, separated by single blank
	 (` ') characters and followed by a newline (`\n') character, to the stan-
	 dard output.
*/

/*echo 'lol' kek 'chebureck'*/
int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (flag == 1 && i > 2)
		printf("%%");
	else if (flag != 1)
		printf("\n");
	return (0);
}
