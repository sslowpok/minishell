/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:15:52 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/19 17:24:58 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/error.h"

/*
** ./pipex file1 cmd1 cmd2 file2
** ./pipex infile "ls -l" "wc -l" outfile
*/

/*
 ** execve(<exact path like "usr/bin/ls">, cmd_flags, envp)
*/

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		inp_error();
	pipex(argv, envp);
	return (0);
}
