/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:50:41 by sslowpok          #+#    #+#             */
/*   Updated: 2022/03/14 09:57:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s)
		i++;
	return (i);
}

static int	ft_len_1(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	if (!i)
		return (1);
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	long int	numb;
	char		*out;

	numb = (long int)n;
	len = ft_len_1(numb);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	if (numb < 0)
	{
		out[0] = '-';
		numb = -numb;
	}
	else if (!numb)
		out[0] = '0';
	out[len] = '\0';
	while (numb)
	{
		out[--len] = (numb % 10) + '0';
		numb /= 10;
	}
	return (out);
}

static int	ft_len_2(unsigned int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	int					len;
	char				*out;

	len = ft_len_2(n);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	if (!n)
		out[0] = '0';
	out[len] = '\0';
	while (n)
	{
		out[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (out);
}
