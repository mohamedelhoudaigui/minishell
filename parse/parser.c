

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


// void  free_tokens(t_oken *token) {
//   while (token->next != NULL) {
//   if (token->token)
//     free(token->token);
//   free(token);
//     token = token->next;
//   }
// }

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
	t_oken	*head;
	head = tokens;
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
	while (tokens->next != NULL)
	{
		tokens = tokens->next;
	}
	if (tokens->data_type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	if (tokens->data_type == REDIR_IN || tokens->data_type == REDIR_OUT || tokens->data_type == HEREDOC
		|| tokens->data_type == APPEND)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	tokens = head; // reset
	// while (tokens->next->next != NULL)
	// {
	// 	if (tokens->next->next == NULL)
	// 		break ;
	// 	tokens = tokens->next;
	// }
	// 	// print_tokens(tokens);
	// if (tokens->next->data_type == REDIR_IN || tokens->next->data_type == REDIR_OUT
	// 	|| tokens->next->data_type == HEREDOC || tokens->next->data_type == APPEND)
	// {
	// 	printf("syntax error near unexpected token `%s'\n", tokens->next->token);
	// 	return (TRUE);
	// }
	// if (tokens->next->data_type == PIPE)
	// {
	// 	printf("syntax error near unexpected token `newline'\n");
	// 	return (TRUE);
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


char    *return_exit_status()
{
    char    *result;
    
    result = ft_itoa(exit_status);
    if (!result)
        return (NULL);
    return (result);
}

char    *chad_expand(t_list **env_var, char *var, t_info *info)
{
    char    *result;
    t_list  *node;
    int     i;
    char    *node_content;

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
            break;
    }
    result = ft_strdup(&node_content[i]);
	add_address(result, info->alloc_head);
    if (!result)
        return (NULL);
    return (result);
}

char    *chad_expand_special(t_list **env_var, char *var, t_info *info)
{
    char    *result;
    t_list  *node;
    int     i;
    char    *node_content;
	char *tmp;

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
            break;
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
	if (file[0] == '$')
		file = chad_expand(info->env, file, info);
	redir = chad_alloc(sizeof(t_redir), 1, info->alloc_head);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;	

	if (cmd->redir_out == NULL)
		cmd->redir_out = redir;
	else
	{
		head = cmd->redir_out;
		while (head->next != NULL)
			head = head->next;
		head->next = redir;
	}
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
	file = tokens->next->token;
	if (file[0] == '$')
		file = chad_expand(info->env, file, info);
	redir = chad_alloc(sizeof(t_redir), 1, info->alloc_head);
	if (tokens->data_type == HEREDOC)
	{
		if (tokens->next->quote_type == 1 || tokens->next->quote_type == 0)
			redir->heredoc_ex = FALSE;
		else	
			redir->heredoc_ex = TRUE;
	}
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

bool	loop_dollar_presence(t_oken *tokens)
{
	int i;

	i =0;
	while (tokens->token[i])
	{
		if (tokens->token[i] == '$')
			return (TRUE);
			i++;
	}
	return (FALSE);
}

bool	check_dollar_presence(t_oken *token)
{
		if (token->token[0] == '$')
			return (TRUE);
	return (FALSE);
}

int		return_dollar_index(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}



// if dollar sign not in quotes do not join
void	handle_word_and_expand(t_oken *tokens, t_info *info, t_cmd *cmd, int i)
{
	t_list 	**env;
	char 		*tmp;
	char 		*expanded;
	char *result;
	unsigned long j = 1;
	int k = 0;

	env = info->env;
	if (loop_dollar_presence(tokens) == TRUE && tokens->quote_type == 1 && tokens->token[0] == '\'')
	{
		tmp = chad_alloc(sizeof(char), ft_strlen(tokens->token) - 1, info->alloc_head);
		while (j < ft_strlen(tokens->token) - 1)
		{
			tmp[k] = tokens->token[j];
			j++;
			k++;
		}
		tmp[k] = '\0';
		expanded = chad_expand(env, tmp, info);
		result = chad_alloc(sizeof(char), ft_strlen(expanded) + 1, info->alloc_head);
		result[0] = '\'';

		j = 1;
		k = 0;
		while (j < ft_strlen(tokens->token) + 3)
		{
			result[j] = expanded[k];
			j++;
			k++;
		}
		result[ft_strlen(expanded) + 1] = '\'';
		result[ft_strlen(expanded) + 2] = '\0';
		cmd->cmd[i] = result;
	}
	else if (tokens->data_type == WORD && tokens->dollar_presence == TRUE && tokens->quote_type != 1 && tokens->quote_type != 0)
	{
		cmd->cmd[i] = chad_expand(env, tokens->token, info);
		return ;
	}
	else if (tokens->quote_type == 0)
	{
		cmd->cmd[i] = tokens->token;
		return ;
	}
	else if (tokens->quote_type== 1)
	{
		cmd->cmd[i] = chad_expand(env, tokens->token, info);
		// cmd->cmd[i] = tokens->token;
		return ;
	}
	// else if (loop_dollar_presence(tokens) == TRUE && tokens->quote_type == 1)
	// {

	// 	puts("dollar presence in quote");
	// 	cmd->cmd[i] = chad_expand(env, tokens->token, info);
	// }
		// cmd->cmd[i] = tokens->token;
	// else if (tokens->dollar_presence == TRUE)
	// 	cmd->cmd[i] = chad_expand(env, tokens->token, info);
	else
		cmd->cmd[i] = tokens->token;
}

t_cmd	*lexer(t_info *info)
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
			continue;
		}if (tokens->data_type == REDIR_OUT || tokens->data_type == APPEND)
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

