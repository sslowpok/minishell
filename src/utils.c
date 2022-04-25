/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:02:42 by sslowpok          #+#    #+#             */
/*   Updated: 2022/04/25 15:12:50 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// void	ft_putendl_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// 	write(fd, "\n", 1);
// }

// char	*ft_strdup(const char *s1)
// {
// 	size_t	i;
// 	char	*out;

// 	i = 0;
// 	if (s1[0] != '\0')
// 		out = malloc((ft_sstrlen(s1) + 1) * sizeof(char));
// 	else
// 		out = malloc(sizeof(char));
// 	if (out == NULL)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		out[i] = s1[i];
// 		i++;
// 	}
// 	out[i] = '\0';
// 	return (out);
// }

// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*out;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	out = malloc(ft_sstrlen(s1) + ft_sstrlen(s2) + 1);
// 	if (!out)
// 		return (0);
// 	while (s1[i])
// 	{
// 		out[j++] = s1[i++];
// 	}
// 	i = 0;
// 	while (s2[i])
// 	{
// 		out[j++] = s2[i++];
// 	}
// 	out[j] = '\0';
// 	return (out);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i] || i == n - 1)
// 			break ;
// 		i++;
// 	}
// 	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
// }

void	total_free(char **arr)
{
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
}
