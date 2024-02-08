/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:34:34 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/08 16:34:40 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

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
		return (return_exit_status());
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
