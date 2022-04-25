/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:47:56 by sslowpok          #+#    #+#             */
/*   Updated: 2022/04/25 15:13:33 by sslowpok         ###   ########.fr       */
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

void	ft_putendl_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
size_t	ft_sstrlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	error(int code, char *text);
void	inp_error(void);
char	**get_paths(char **envp);
char	**paths_fill(char **paths);
void	total_free(char **arr);
char	*make_cmd(char **paths, char **cmd_flags);
void	execute_cmd(char *arg, char **envp);

#endif