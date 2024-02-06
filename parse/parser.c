

#include "../inc/parse.h"



t_cmd	*parser(t_info *info)
{
	int		word_count;
	t_cmd	*cmd;
	t_cmd	*head;
	t_oken	*tokens;
	t_list	**env;
	int		i;

	tokens = info->head;
	env = info->env;
	if (check_token_syntax(tokens))
		return (NULL);
	word_count = words_before_pipe(tokens) + 1;
	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	head = cmd;
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	i = 0;
	while (tokens != NULL)
	{
		if (tokens->data_type == PIPE)
		{
			cmd->cmd[i] = NULL;
			cmd->next = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
			cmd = cmd->next;
			cmd->redir = NULL;
			cmd->redir_out = NULL;
			word_count = words_before_pipe(tokens->next) + 1;
			cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
			tokens = tokens->next;
			i = 0;
			continue ;
		}
		if (tokens->data_type == REDIR_OUT || tokens->data_type == APPEND)
		{
			handle_redir_out(tokens, info, cmd);
			tokens = tokens->next->next;
			continue ;
		}
		if (tokens->data_type == REDIR_IN || tokens->data_type == HEREDOC)
		{
			handle_redir_in(tokens, info, cmd);
			tokens = tokens->next->next;
			continue ;
		}
		if (tokens->data_type == WORD)
		{
			handle_word_and_expand(tokens, info, cmd, i);
		}
		if (tokens->next == NULL)
		{
			cmd->cmd[i + 1] = NULL;
			break ;
		}
		tokens = tokens->next;
		i++;
	}
	info->cmd = head;
	return (head);
}
