/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:58:50 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 20:18:56 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

const char	*translate(int c)
{
	if (c == 1)
		return ("REDIR_IN");
	if (c == 2)
		return ("REDIR_OUT");
	if (c == 3)
		return ("HEREDOC");
	if (c == 4)
		return ("APPEND");
	if (c == 5)
		return ("PIPE");
	if (c == 6)
		return ("WORD");
	return (NULL);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i] != NULL)
	{
		printf("cmd token[%d]=>%s\n", i, cmd->cmd[i]);
		i++;
	}
	printf("%s\n", cmd->cmd[i]);
}

void	print_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir == NULL)
			break ;
		printf("file => %s | type => %s\n", redir->file,
			translate(redir->type));
		redir = redir->next;
	}
}
void print_tokens(t_oken *head_token) 
{
  t_oken *ptr = head_token;
  while (ptr->next != NULL) {
    printf("token :%s--quote value =>%d--type =>%s , join_next : %d | dollar presence : %d\n", ptr->token,
           ptr->quote_type, translate(ptr->data_type), ptr->join_next, ptr->dollar_presence);
    ptr = ptr->next;
  }
    printf("token :%s--quote value =>%d--type =>%s , join_next : %d | dollar presence : %d\n", ptr->token,
           ptr->quote_type, translate(ptr->data_type), ptr->join_next, ptr->dollar_presence);
}

void	print_all_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		print_cmd(cmd);
		cmd = cmd->next;
		if (cmd == NULL)
			break ;
	}
}

void	print_cmd_and_redir(t_cmd *cmd)
{
	print_all_cmd(cmd);
	print_redir(cmd->redir);
	print_redir(cmd->redir_out);
}
