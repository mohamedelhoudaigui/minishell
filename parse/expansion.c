/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:34:34 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/09 22:38:36 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

bool	prev_is_heredoc(t_oken *tokens)
{
	if (tokens->prev != NULL)
	{
		if (tokens->prev->data_type == HEREDOC)
			return (TRUE);
	}
	return (FALSE);
}

bool	check_dollar_presence(t_oken *token)
{
	if (token->token[0] == '$')
		return (TRUE);
	return (FALSE);
}

char	*chad_expand(t_list **env_var, char *var, t_info *info)
{
	char	*result;
	t_list	*node;
	int		i;
	char	*node_content;

	if (!var)
		return (NULL);
	if (var[1] == '?' && var[2] == '\0')
		return (return_exit_status(info));
	var++;
	node = ft_lstfind_str(env_var, var);
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
	if (!result)
		return (NULL);
	return (result);
}

void	expand_tokens(t_info *info)
{
	t_oken	*tokens;

	tokens = info->head;
	while (tokens)
	{
		if (tokens->quote_type == DQUOTE && token_dollar_count(tokens) > 0
			&& tokens->data_type == WORD && tokens->quote_type != QUOTE
			&& prev_is_heredoc(tokens) == FALSE)
			tokens->token = ultimate_expander(tokens, info);
		if (token_dollar_count(tokens) > 0 && tokens->data_type == WORD
			&& tokens->quote_type != QUOTE && prev_is_heredoc(tokens) == FALSE)
			tokens->token = ultimate_expander(tokens, info);
		tokens = tokens->next;
	}
}
