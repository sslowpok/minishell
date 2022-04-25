/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:07:21 by alex              #+#    #+#             */
/*   Updated: 2022/03/18 17:48:29 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../printf/ft_printf.h"

# define INPUT	0
# define OUTPUT	1

typedef struct s_child
{
	char	*path;
	char	**envp;
	pid_t	child1;
	pid_t	child2;
	int		fd[2];
}			t_child;

void	ft_putendl_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_sstrlen(const char *str);
void	child_one(t_child *child, char **argv, char **envp);
void	child_two(t_child *child, char **argv, char **envp);
void	pipex(char **argv, char **envp);
void	inp_error(void);
void	execute_cmd(t_child *child, char *arg, char **envp);
char	**paths_fill(char **paths);

#endif