/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:47:11 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/20 17:33:11 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

void	error(int code, char *text)
{
	if (code == -1)
	{
		write(2, text, ft_strlen(text));
		write(2, " command not found\n", 20);
		exit (1);
	}
	perror(text);
	exit (1);
}

void	inp_error(void)
{
	ft_putendl_fd("Invalid input.", 2);
	exit(1);
}
