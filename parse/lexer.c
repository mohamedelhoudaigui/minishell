

#include "../inc/parse.h"


bool	is_op(int op)
{
	if (op != 6)
		return (TRUE);
	return (FALSE);
}

int	pipe_count(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5)
			count++;
		tokens = tokens->next;
	}
	return (count + 1);
}

int	redir_count(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 2 || tokens->data_type == 3
			|| tokens->data_type == 4)
			count++;
		tokens = tokens->next;
	}
	return (count);
}


void  free_tokens(t_oken *token) {
  while (token->next != NULL) {
  if (token->token)
    free(token->token);
  free(token);
    token = token->next;
  }
}

void print_cmd(t_cmd *cmd) {
  int i = 0;
  while (cmd->cmd[i] != NULL) {
    printf("cmd token[%d]=>%s\n", i, cmd->cmd[i]);
    i++;
  }
    printf("%s\n", cmd->cmd[i]);
}


bool	check_token_syntax(t_oken *tokens)
{
//	free on exit
	if (tokens->data_type != WORD && tokens->data_type != PIPE && tokens->next != NULL)
	{
		if (tokens->next->data_type == WORD)
			return (FALSE);
		if (tokens->next->data_type != WORD && tokens->next->data_type != PIPE)
		{
				printf("syntax error near unexpected token `%s'\n", tokens->next->token);
				return (TRUE);
		}
		printf("syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	else if (tokens->data_type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	while (tokens->next)
	{
		tokens = tokens->next;
	}
	if (tokens->data_type == PIPE)
		return (TRUE);
	// while (tokens)
	// {
	// 	if (tokens == NULL)
	// 		break ;
	// 	if (tokens->data_type == REDIR_IN || tokens->data_type == REDIR_OUT || tokens->data_type == HEREDOC
	// 		|| tokens->data_type == APPEND || tokens->data_type == PIPE)
	// 	{
	// 		if (tokens->next == NULL)
	// 		{
	// 			printf("syntax error near unexpected token `newline'\n");
	// 			return (TRUE);
	// 		}				
	// 		else if (tokens->next->data_type != WORD)
	// 			{
	// 				printf("syntax error near unexpected token `%s'\n", tokens->token);
	// 				return (TRUE);
	// 			}
	// 	}
	// 	tokens = tokens->next;
	// }
	return (FALSE);
}
int	words_before_pipe(t_oken *tokens)
{
	int		count;

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


void	print_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir == NULL)
			break ;
		printf("file => %s | type => %s\n", redir->file, translate(redir->type));
		redir = redir->next;
	}
}

void	handle_redir_out(t_oken *tokens, t_info *info, t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*head;
	char	*file;
	int		type = -1;

	if (tokens->data_type == REDIR_OUT)
		type = REDIR_OUT;
	else if (tokens->data_type == APPEND)
		type = APPEND;
	file = tokens->next->token;
	redir = chad_alloc(sizeof(t_redir), 1, info->alloc_head);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	//needs to iterate through the cmd list
	if (cmd->redir_out == NULL)
		cmd->redir_out = redir;
	else
	{
		head = cmd->redir_out;
		while (head->next != NULL)
			head = head->next;
		head->next = redir;
	}
	print_redir(redir);
}

void	handle_redir_in(t_oken *tokens, t_info *info, t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*head;
	char	*file;
	int		type = -1;

	if (tokens->data_type == REDIR_IN)
		type = REDIR_IN;
	else if (tokens->data_type == HEREDOC)
		type = HEREDOC;
	file = tokens->next->token; // need to check if this is a word
	redir = chad_alloc(sizeof(t_redir), 1, info->alloc_head);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	if (cmd->redir == NULL)
		cmd->redir = redir;
	else
	{
		head = cmd->redir;
		while (head->next != NULL)
			head = head->next;
		head->next = redir;
	}
}

t_cmd	*lexer(t_info *info)
{
	int		word_count;
	t_cmd	*cmd;
	t_cmd	*head;
	t_oken	*tokens;
	int		i;

	tokens = info->head;
	if (check_token_syntax(tokens))
		return (NULL);
	word_count = words_before_pipe(tokens) + 1;
	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	head = cmd;
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	// print_tokens(tokens);
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
			// continue;
		}else if (tokens->data_type == REDIR_OUT || tokens->data_type == APPEND)
		{
			handle_redir_out(tokens, info, cmd);
			tokens = tokens->next->next;
			continue ;
		}
		else if (tokens->data_type == REDIR_IN || tokens->data_type == HEREDOC)
		{
			handle_redir_in(tokens, info, cmd);
			tokens = tokens->next->next;
			continue ;
		}

		if (tokens->data_type == WORD)
		{
			cmd->cmd[i] = tokens->token;
			// if (tokens->dollar_presence == TRUE)
				// expanded_var(t_list **env_var, char *var); prototype
				// cmd->var = add_var(tokens->token, info);
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

