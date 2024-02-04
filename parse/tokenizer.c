
#include "../inc/parse.h"
#include "../inc/execution.h"

bool check_line(char *line, t_info *info) // for checking early parse errors
{
  if (!valid_quotes(info))
    return FALSE;
  while (line[info->cursor]) {
    if (!is_space(line[info->cursor])) 
      return TRUE;
    info->cursor += 1;
  }
  return FALSE;
} // such ar the '=' at the beggining

void default_token(t_oken *head) {
  // default values for the token node;
  if (!head->next || !head->prev) {
    head->next = NULL;
    head->prev = NULL;
  }
  head->dollar_presence = FALSE;
  head->quote_type = -1;
  head->data_type = -1;
}
// allocate for the token outside
t_oken *add_token(char *str_token, t_info *info) {
  size_t size = sizeof(t_oken);
  // t_oken *iter = info->head;
  t_oken *head = info->head;
  if (!info->head) {
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    info->head = token;
    default_token(token);
    token->token = str_token;
    return (token);
  } else {
    while (head->next != NULL) {
      head = head->next;
    }
    t_oken *token = chad_alloc(size, 1, info->alloc_head);
    default_token(token);
    head->next = token;
    token->prev = head;
    token->next = NULL;
    token->token = str_token;
    return (token);
  }
}

void  handle_pipe(t_info *info)
{
  t_oken *new_token;
    char *str_token = chad_alloc(1, 2, info->alloc_head);
    str_token[0] = PIPE_CHAR;
    str_token[1] = '\0';
    new_token = add_token(str_token, info);
    new_token->data_type = PIPE;
    info->cursor += 1;
}

void handle_operator(char *line, t_info *info) {
  t_oken *new_token;
  if (line[info->cursor] == PIPE_CHAR){
    handle_pipe(info);
  }
  else if (line[info->cursor] == REDIR_OUT_CHAR) {
    if ((line[info->cursor + 1]) == REDIR_OUT_CHAR) {
      char *str_token = chad_strdup(">>", info->alloc_head);
        new_token = add_token(str_token, info);
      new_token->data_type = 4;
      info->cursor += 2;
    } else {
      char *str_token = chad_strdup(">",  info->alloc_head);
      new_token = add_token(str_token, info);
      new_token->data_type = 2;
      info->cursor += 1;
    }
  } else if (line[info->cursor] == REDIR_IN_CHAR) {
    if (line[info->cursor + 1] == REDIR_IN_CHAR) {
      char *str_token = chad_strdup("<<", info->alloc_head);
      new_token = add_token(str_token, info);
      new_token->data_type = 3;
      info->cursor += 2;
    } else {
      char *str_token = chad_strdup("<",  info->alloc_head);
      new_token = add_token(str_token, info);
      new_token->data_type = 1;
      info->cursor += 1;
    }
  }
}


// not fin
void  join_quotes(t_oken *head, t_info *info)
{
  t_oken *token = head;
  t_oken *next = head->next;
  while (next)
  {
    if (/*token->quote_type == next->quote_type && */token->join_next == TRUE)
    {
      token->token = chad_strjoin(token->token, next->token, info->alloc_head);
      token->next = next->next;
      next = next->next;
    }
    else
    {
      token = next;
      next = next->next;
    }
  }
}

t_oken *handle_quote(char *line, t_info *info) {
  // handling quotes by taking everything inside them regardless;
  // update quote type
  //quotes not working if they are the last token
  char *str_token;
  t_oken *new_token;
  int j = 0;
  info->cursor += 1;
  int i = info->cursor;
  int len = quote_len(line, info);
  if (len == -1)
    return NULL;
  str_token = (char *)chad_alloc(1, len + 1, info->alloc_head);
  while (j < len && str_token[j] && line[i]) {
    str_token[j] = line[i];
    j++;
    i++;
  }
  str_token[len] = '\0';
  new_token = add_token(str_token, info);

  if (line[info->cursor - 1] == DQUOTE)
    new_token->quote_type = 1;
  else
    new_token->quote_type = 0;
  new_token->data_type = WORD;
  // does not support different quotes joining
  // flag the in handle_word and join them
  if (line[i + 1] == DQUOTE && new_token->quote_type == 1)
    new_token->join_next = TRUE;
  else if (line[i + 1] == QUOTE && new_token->quote_type == 0)
    new_token->join_next = TRUE;
  else
    new_token->join_next = FALSE;
  info->cursor += j + 1;
  return (new_token);
}

t_oken *handle_word(char *line, t_info *info) {
  char *str_token;
  t_oken *new_token;
  int j = 0;
  int i = info->cursor;
  int len = word_len(info);
  str_token = chad_alloc(sizeof(char), len + 1, info->alloc_head); // segv here
  while (j < len) {
    str_token[j] = line[i];
    j++;
    i++;
  }
  str_token[len] = '\0';
  // word + quotes are joinning, but quotes + word are not
  new_token = add_token(str_token, info);
    if (line[i] == DQUOTE)
    new_token->join_next = TRUE;
  else if (line[i] == QUOTE)
    new_token->join_next = TRUE;
  else
    new_token->join_next = FALSE;

  info->cursor = i;
  new_token->data_type = 6;
  return (new_token);
}

void handle_dollar(char *line, t_info *info) {
  t_oken *new_token = handle_word(line, info);
  new_token->dollar_presence = TRUE;
}

t_info *tokenizer(char *line, t_info *info) {

  if (!check_line(line, info))
    return NULL;
  while (line[info->cursor]) {
    if (is_operator(line[info->cursor]))
    {
      handle_operator(line, info);
    }
    else if (line[info->cursor] == DQUOTE || line[info->cursor] == QUOTE)
    {
      handle_quote(line, info);
    }
    else if (ft_isprint(line[info->cursor]) && !is_space(line[info->cursor]) && !is_operator(line[info->cursor]) && !is_quote(line[info->cursor]))
    {

      handle_word(line, info);
    }
    else if (line[info->cursor] == '$')
      handle_dollar(line, info);
    else if (is_space(line[info->cursor]))
      info->cursor++;
  }
  return (info);
}
void f(void)
{
  fprintf(stderr, "exiting\n");
  system("leaks minishell");
}


void print_all_cmd(t_cmd *cmd) 
{
  while (cmd) {
    print_cmd(cmd);
    cmd = cmd->next;
    if (cmd == NULL)
      break;
  }
}

void print_cmd_and_redir(t_cmd *cmd) {
  print_all_cmd(cmd);
  print_redir(cmd->redir);
  print_redir(cmd->redir_out);
}


bool  line_is_empty(char *line)
{
  int i = 0;
  while (line[i])
  {
    if (line[i] != ' ')
      return FALSE;
    i++;
  }
  return TRUE;
}

void  chad_free(t_info *info, t_alloc *alloc_head)
{
  free(info->line);
  free(info);
  free_all(alloc_head);
}

void  linker(t_info *info, t_list **env_adr)
{
  t_commands  *exec_coms;
  int   o_stdin;
  int   o_stdout;

  o_stdin = dup(0);
  o_stdout = dup(1);
    exec_coms = open_fd(info->cmd, env_adr);
    execution(env_adr, exec_coms);
    close_all_fd(exec_coms);
    ft_clear_commands(&exec_coms);
    reset_fd(o_stdin, o_stdout);

}

void  chad_readline(t_info *info, t_alloc *alloc_head, t_list **env_adr)
{
  char *line;
  t_cmd *cmd;

  
    info->cursor = 0;
    line = readline("Lbroshell$ ");
    if (!line)
    {
      chad_free(info ,alloc_head);
      printf("\nexit\n");
      exit(exit_status);
    }
    if (line[0] == '\0' || line_is_empty(line))
    {
      chad_free(info, alloc_head);
      return;
    }
    // else if (strcmp(line, "exit") == 0)
    // {
    //   chad_free(info, alloc_head);

    //   // atexit(f);
    //   exit(0);
    // }
    add_history(line);
    info->line = line;
    if (!tokenizer(line, info))
    {
      chad_free(info, alloc_head);
      return;
    }
    join_quotes(info->head, info);
    // print_tokens(info->head);
    cmd = lexer(info);
    if(cmd == NULL)
    {
      chad_free(info, alloc_head);
      return;
    }
    /// morph args;
    linker(info, env_adr);
    chad_free(info, alloc_head);
}

void  main_loop(t_list **env_adr)
{
  t_info *info;
  t_alloc *alloc_head;


  while (TRUE)
  {
    signal(SIGQUIT, SIG_IGN);
   info = ft_calloc(1, sizeof(t_info));
    alloc_head = ft_calloc(1, sizeof(t_alloc));
    alloc_head->next = NULL;
    alloc_head->address = ft_strdup("placeholder");
    info->alloc_head = alloc_head;
    info->head = NULL;
    chad_readline(info, alloc_head, env_adr);
    // printf("%p\n", coms);
  }
}