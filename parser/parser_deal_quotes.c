/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_deal_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:27:34 by coverand          #+#    #+#             */
/*   Updated: 2022/05/20 19:40:34 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/builtins.h"

static char	*ft_dollar_question(void)
{
	char	*return_val;
	char	*en;
	int		k;

	en = ft_strdup("");
	k = 0;
	return_val = ft_itoa(g_global.last_return);
	while (return_val[k])
		en = ft_strjoin_mod(en, return_val[k++]);
	return (en);
}

static char	*ft_check_dollar(char *str, int *j, char *to_copy, t_llist *envp)
{
	char	*en;
	int		i;
	char	*val;

	en = ft_strdup("");
	i = *j;
	i++;
	if (to_copy[i] == '?')
	{
		*j = ++i;
		return (ft_strjoin(str, ft_dollar_question()));
	}
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

char	*ft_delete_quotes_help(char *str, int *j, t_list *t, t_llist *envp)
{	
	int	i;

	i = *j;
	if (((char *)t->content)[i] == 39)
		str = ft_deal_single_quote(str, &i, (char *)t->content);
	if (((char *)t->content)[i] == 34)
		str = ft_deal_double_quote(str, &i, (char *)t->content, envp);
	*j = i;
	return (str);
}

int	ft_delete_quotes(t_list **cmd, t_llist *envp)
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
			if (((char *)t->content)[i] == 39 || ((char *)t->content)[i] == 34)
				str = ft_delete_quotes_help(str, &i, t, envp);
			if (((char *)t->content)[i] == '$' && ((char *)t->content)[i + 1])
				str = ft_check_dollar(str, &i, (char *)t->content, envp);
			if ((((char *)t->content)[i] && ((char *)t->content)[i] != 34 && \
			((char *)t->content)[i] != 39 && ((char *)t->content)[i] != '$') || \
			(((char *)t->content)[i] == '$' && !((char *)t->content)[i + 1]))
				str = ft_strjoin_mod(str, ((char *)t->content)[i++]);
		}
		t->content = (void *)ft_strdup(str);
		free(str);
		t = t->next;
	}
	return (0);
}
