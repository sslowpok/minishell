/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_deal_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:27:34 by coverand          #+#    #+#             */
/*   Updated: 2022/05/06 18:30:07 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/*
Examples:
1) echo 'lol'
lol

2) echo "lol"
lol

3) echo '$PATH'
$PATH

4) echo "$PATH"
/Users/coverand/.brew/bin:/usr/local/bin:/usr/
sbin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin

5) echo $$ 
> PID

6) echo $, echo '$', echo "$"
$

7) echo "$?", echo $?
>> show return

8) echo "m$?"
m0

9) echo "m$PATH"
m/Users/coverand/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin

10) echo lol'meow', echo lol"meow"
lolmeow
*/

/*
1) If we have no quotes -> check whether there is $
- if there is no symbols after $ -> str = [everything before $ sign] + [$]
- if there is smth after $  ->  str = [everything before $ sign] + [viriable from env]
2) If we have single quotes -> just get rid of the quotes
3) If we have double quotes -> get rid of quotes and go to p 1.
*/

char	*ft_strjoin_mod(char const *s1, char ch)
{
	int		len1;
	char	*str;
	int		i;

	/*if (!s1)
		return (0);*/
	i = 0;
	len1 = ft_strlen(s1);
	str = malloc(sizeof(*str) * (len1 + 1) + 1);
	if (str == 0)
		return (0);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = ch;
	i++;
	str[i] = '\0';
	return (str);
}

char	*ft_deal_single_quote(char *str, int *j, char *to_copy)
{
	int		i;

	i = *j;
	i++;
	while (to_copy[i] != 39)
	{
		str = ft_strjoin_mod(str, to_copy[i]);
		i++;
	}
	i++;
	*j = i;
	return (str);
}

char	*ft_check_dollar(char *str, int *j, char *to_copy, t_llist *envp, int __unused flag)
{
	char	*en;
	int		i;

	i = *j;
	en = ft_strdup("");
	i++;
	while (to_copy[i] != 34 && to_copy[i] != 39 && \
	to_copy[i] && to_copy[i] != '$')
	{
		en = ft_strjoin_mod(en, to_copy[i]);
		i++;
	}
	str = ft_strjoin(str, ft_get_value_envp(&envp, en));
	printf("end: %i, %c\n", i, to_copy[i]);
	*j = i;
	return (str);
}

char	*ft_deal_double_quote(char *str, int *j, char *to_copy, t_llist *envp)
{
	int		i;

	i = *j;
	i++;
	while (to_copy[i] != 34)
	{
		if (to_copy[i] == '$' && to_copy[i + 1] != 34)
			str = ft_check_dollar(str, &i, to_copy, envp, 1);
		else
		{
			str = ft_strjoin_mod(str, to_copy[i]);
			i++;
		}
	}
	i++;
	*j = i;
	return (str);
}

int	ft_delete_quotes(t_list **cmd, t_llist __unused *envp)
{
	char	*str;
	t_list	*tmp;
	int		i;

	tmp = *cmd;
	while (tmp)
	{
		i = 0;
		str = ft_strdup("");
		while (((char *)tmp->content)[i])
		{
			if (((char *)tmp->content)[i] == 39)
				str = ft_deal_single_quote(str, &i, (char *)tmp->content);
			if (((char *)tmp->content)[i] == 34)
				str = ft_deal_double_quote(str, &i, (char *)tmp->content, envp);
			if ((((char *)tmp->content)[i] != 39 && \
			((char *)tmp->content)[i] != 34) && ((char *)tmp->content)[i])
			{
				str = ft_strjoin_mod(str, ((char *)tmp->content)[i]);
				i++;
			}
		}
	/*	if ((char *)tmp->content)
			free((char *)tmp->content);*/
	//	tmp->content = NULL;
		tmp->content = (void *)ft_strdup(str);
		free(str);
		printf("content: %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}
