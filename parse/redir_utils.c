/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:50:17 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 23:27:19 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	loop_dollar_presence(t_oken *tokens)
{
	int	i;

	i = 0;
	while (tokens->token[i])
	{
		if (tokens->token[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	words_before_pipe(t_oken *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5 || tokens == NULL)
			return (count);
		else
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	*chad_substr(char const *s, unsigned int start, size_t len,
		t_info *info)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (chad_strdup("", info->alloc_head));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	res = chad_alloc(sizeof(char), len + 1, info->alloc_head);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

int	return_dollar_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*bro_lstfind(char *res, t_info *info)
{
	char	*expand_to;
	int		i;
	char	*r;

	i = 0;
	while (res[i])
	{
		if (res[i] == '$' || res[i] == ' ' || res[i] == '-'
			|| res[i] == QUOTE_CHAR || res[i] == DQUOTE_CHAR)
			break ;
		i++;
	}
	expand_to = chad_substr(res, 0, i, info);
	r = chad_strjoin(expand_to, "=", info->alloc_head);
	return (r);
}
