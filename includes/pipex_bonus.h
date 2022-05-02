/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:47:56 by sslowpok          #+#    #+#             */
/*   Updated: 2022/05/02 13:37:32 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# include "../libft/libft.h"

# define INPUT	0
# define OUTPUT	1

typedef struct s_child
{
	char	*path;
	char	**envp;
	int		fd[2];
	int		fd_in;
	int		fd_out;
}			t_child;

#endif