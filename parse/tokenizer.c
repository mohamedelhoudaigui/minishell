/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:48 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/05 10:30:58by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/parse.h"
#include "../inc/execution.h"

bool check_line(char *line, t_info *info) // for checking early parse errors
{
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
    if (token->join_next == TRUE)
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

t_oken *handle_quote(char *line, t_info *info) {
  char *str_token;
  t_oken *new_token;
  int j = 0;

  info->cursor += 1;
  if (!valid_quotes(info))
  {
    parse_error("syntax error : invalid quotes", info);
    chad_free(info, info->alloc_head);
  }
  int i = info->cursor;
  int len = quote_len(line, info);
  if (len == -1)
    return NULL;
  str_token = (char *)chad_alloc(1, len + 1, info->alloc_head);
  while (j < len) {
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
  if (line[i + 1] == DQUOTE && line[i + 1] != '\0')
    new_token->join_next = TRUE;
  else if (line[i + 1] == QUOTE && line[i + 1] != '\0' && line[i + 1])
    new_token->join_next = TRUE;
  else if (line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != PIPE_CHAR && line[i + 1] != REDIR_OUT_CHAR && line[i + 1] != REDIR_IN_CHAR )
    new_token->join_next = TRUE;
  else
    new_token->join_next = FALSE;
  info->cursor += j + 1;
  return (new_token);
}



void handle_dollar(char *line, t_info *info) {
  t_oken *new_token = handle_word(line, info);
  new_token->dollar_presence = TRUE;
  // print_tokens(info->head);
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
    else if (ft_isprint(line[info->cursor]) && !is_space(line[info->cursor]) && !is_operator(line[info->cursor]) && !is_quote(line[info->cursor]) && line[info->cursor] != '$')
    {

      handle_word(line, info);
    }
    else if (line[info->cursor] == '$') // tokenize everything dollar as word then expand
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


