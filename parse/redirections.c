/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:54:54 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 23:27:07 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int	token_dollar_count(t_oken *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens->token[i])
	{
		if (tokens->token[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*chad_expand_len(t_list **env_var, char *var, t_info *info)
{
	char	*result;
	t_list	*node;
	int		i;
	char	*node_content;
	char	*tmp;

	if (!var)
		return (NULL);
	if (var[1] == '?' && var[2] == '\0')
		return (return_exit_status(info));
	var++;
	tmp = bro_lstfind(var, info);
	node = ft_lstfind_str(env_var, tmp);
	if (!node || !node->content)
		return (chad_strdup("", info->alloc_head));
	node_content = (char *)node->content;
	i = -1;
	while (node_content[++i])
	{
		if (node_content[i - 1] == '=')
			break ;
	}
	result = chad_strdup(&node_content[i], info->alloc_head);
	return (result);
}

int	get_var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != ' ' && var[i] != '\0' && var[i] != '$')
		i++;
	return (i);
}

void	expander_loop(t_oken *tokens, int *j)
{
	*j += 1;
	while (tokens->token[*j])
	{
		if (tokens->token[*j] == ' ' || tokens->token[*j] == '$'
			|| tokens->token[*j] == '-' || tokens->token[*j] == QUOTE_CHAR
			|| tokens->token[*j] == DQUOTE_CHAR)
			break ;
		*j += 1;
	}
}

char	*ultimate_expander(t_oken *tokens, t_info *info)
{
	int		j;
	char	*expanded;
	char	*word;
	int		p;
	int		o;

	j = 0;
	p = 0;
	word = chad_alloc(sizeof(char), 1000, info->alloc_head);
	while (tokens->token[j])
	{
		if (tokens->token[j] == '$')
		{
			expanded = chad_expand_len(info->env, &tokens->token[j], info);
			o = -1;
			while (expanded[++o])
				word[p++] = expanded[o];
			expander_loop(tokens, &j);
		}
		else
			word[p++] = tokens->token[j++];
	}
	return (word);
}
