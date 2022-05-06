/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_deal_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:27:34 by coverand          #+#    #+#             */
/*   Updated: 2022/05/06 19:10:00 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

// TO BE ADDED: $? AND $$

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

static char	*ft_strjoin_mod(char const *s1, char ch)
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

/*Put every symbol from to_copy to str till closing single quote*/
static char	*ft_deal_single_quote(char *str, int *j, char *to_copy)
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

/*
Create new string env, which contains all symbols from to_copy
(from $ to $ 
or from $ to single quote
or from $ to double quote
or from $ to the end of to_copy)

Find varible in envp that has env as key and return its value.
Join this value to the string content (str).
return str.
*/
static char	*ft_check_dollar(char *str, int *j, char *to_copy, t_llist *envp)
{
	char	*en;
	int		i;
	char	*val;

	i = *j;
	en = ft_strdup("");
	i++;
	while (to_copy[i] != 34 && to_copy[i] != 39 && \
	to_copy[i] && to_copy[i] != '$')
	{
		en = ft_strjoin_mod(en, to_copy[i]);
		i++;
	}
	val = ft_get_value_envp(&envp, en);
	if (val)
		str = ft_strjoin(str, val);
	free(en);
	free(val);
	*j = i;
	return (str);
}

/*
Put every symbol from to_copy to str till closing single quote.
If you found $ -> join to str result that you get from ft_check_dollar function.
*/
static char	*ft_deal_double_quote(char *str, int *j, \
char *to_copy, t_llist *envp)
{
	int		i;

	i = *j;
	i++;
	while (to_copy[i] != 34)
	{
		if (to_copy[i] == '$' && to_copy[i + 1] != 34)
			str = ft_check_dollar(str, &i, to_copy, envp);
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
	t_list	*t;
	int		i;

	t = *cmd;
	while (t)
	{
		i = 0;
		str = ft_strdup("");
		while (((char *)t->content)[i])
		{
			if (((char *)t->content)[i] == 39)
				str = ft_deal_single_quote(str, &i, (char *)t->content);
			if (((char *)t->content)[i] == 34)
				str = ft_deal_double_quote(str, &i, (char *)t->content, envp);
			if (((char *)t->content)[i] == '$' && ((char *)t->content)[i + 1])
				str = ft_check_dollar(str, &i, (char *)t->content, envp);
			if ((((char *)t->content)[i] && ((char *)t->content)[i] != 34 && \
			((char *)t->content)[i] != 39) || \
			(((char *)t->content)[i] == '$' && !((char *)t->content)[i + 1]))
			{
				str = ft_strjoin_mod(str, ((char *)t->content)[i]);
				i++;
			}
		}
		t->content = (void *)ft_strdup(str);
		free(str);
		printf("content: %s\n", (char *)t->content);
		t = t->next;
	}
	return (0);
}
