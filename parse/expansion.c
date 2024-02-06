/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:34:34 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 19:00:57 by mlamkadm         ###   ########.fr       */
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
		return (NULL);
	node_content = (char *)node->content;
	i = -1;
	while (node_content[++i])
	{
		if (node_content[i - 1] == '=')
			break ;
	}
	result = ft_strdup(&node_content[i]);
	add_address(result, info->alloc_head);
	if (!result)
		return (NULL);
	return (result);
}

char	*chad_expand_special(t_list **env_var, char *var, t_info *info)
{
	char	*result;
	t_list	*node;
	int		i;
	char	*node_content;
	char	*tmp;

	if (!var)
		return (NULL);
	node = ft_lstfind_str(env_var, var);
	if (!node || !node->content)
		return (NULL);
	node_content = (char *)node->content;
	i = -1;
	while (node_content[++i])
	{
		if (node_content[i - 1] == '=')
			break ;
	}
	result = ft_strdup(&node_content[i]);
	tmp = chad_alloc(sizeof(char), ft_strlen(result) + 3, info->alloc_head);
	tmp[0] = '\'';
	while (result[++i])
		tmp[i] = result[i];
	tmp[i] = '\'';
	free(result);
	return (tmp);
}