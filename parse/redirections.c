/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:49:24 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/07 02:10:44 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

char	*handle_word_and_expand2(t_oken *tokens, t_info *info, char **result,
		char **tmp)
{
	int				k;
	unsigned long	j;
	char			*expanded;

	k = 0;
	j = 0;
	(*tmp) = chad_alloc(sizeof(char), ft_strlen(tokens->token) - 1,
			info->alloc_head);
	while (++j < ft_strlen(tokens->token) - 1)
		(*tmp)[k++] = tokens->token[j];
	(*tmp)[k] = '\0';
	expanded = chad_expand(info->env, (*tmp), info);
	*result = chad_alloc(sizeof(char), ft_strlen(expanded) + 1,
			info->alloc_head);
	return (expanded);
}

void	handle_word_and_expand3(t_info *info, t_cmd *cmd, t_oken *tokens, int i)
{
	t_list	**env;

	env = info->env;
	if (tokens->data_type == WORD && tokens->dollar_presence == TRUE
		&& tokens->quote_type != 1 && tokens->quote_type != 0)
		cmd->cmd[i] = chad_expand(env, tokens->token, info);
	else if (tokens->quote_type == 0)
		cmd->cmd[i] = tokens->token;
	else if (tokens->quote_type == 1)
		cmd->cmd[i] = chad_expand(env, tokens->token, info);
}

void	handle_word_and_expand4(char *result, char *expanded, t_cmd *cmd, int i)
{
	result[ft_strlen(expanded) + 1] = '\'';
	result[ft_strlen(expanded) + 2] = '\0';
	cmd->cmd[i] = result;
}

void	handle_word_and_expand5(char **result, unsigned long *j,
		unsigned long *k, char **expanded)
{
	(*result)[*j] = (*expanded)[*k];
	(*j)++;
	(*k)++;
}

void	handle_word_and_expand(t_oken *tokens, t_info *info, t_cmd *cmd, int i)
{
	t_list			**env;
	char			*tmp;
	char			*expanded;
	char			*result;
	unsigned long	j[2];

	(j[0]) = 0;
	j[1] = 0;
	env = info->env;
	if (tokens->data_type == WORD && loop_dollar_presence(tokens) == FALSE)
		cmd->cmd[i] = tokens->token;
	else if (loop_dollar_presence(tokens) == TRUE && tokens->quote_type == 1
		&& tokens->token[0] == '\'')
	{
		expanded = handle_word_and_expand2(tokens, info, &result, &tmp);
		result[0] = '\'';
		(j[0]) = 1;
		j[1] = 0;
		while ((j[0]) < ft_strlen(tokens->token) + 3)
			handle_word_and_expand5(&result, &(j[0]), &(j[1]), &expanded);
		handle_word_and_expand4(result, expanded, cmd, i);
	}
	else
		handle_word_and_expand3(info, cmd, tokens, i);
}
