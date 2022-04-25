/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:40:19 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/16 17:40:27 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_sstrlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_sstrlen(src));
}

static int	ft_word_count(const char *s, char c)
{
	int	i;
	int	word_count;
	int	len;
	int	ss;

	len = 0;
	ss = 0;
	while (s[len])
		len++;
	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && ss == 0)
		{
			ss = 1;
			word_count++;
		}
		else if (s[i] == c)
			ss = 0;
		i++;
	}
	return (word_count);
}

static char	*ft_str_create(const char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

static void	ft_clear(char **arr, int i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr);
}

char	**ft_split(const char *s, char c)
{
	char	**out;
	int		i;
	int		word_count;

	if (!s)
		return (NULL);
	i = -1;
	word_count = ft_word_count(s, c);
	out = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!out)
		return (NULL);
	while (++i < word_count)
	{
		while (*s == c)
			s++;
		out[i] = ft_str_create(s, c);
		if (!out)
		{
			ft_clear(out, i);
			return (NULL);
		}
		s = s + ft_sstrlen(out[i]);
	}
	out[i] = 0;
	return (out);
}
