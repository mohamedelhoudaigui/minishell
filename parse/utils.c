

#include "../inc/parse.h"

void parse_error(const char *exit_msg, t_info *info) {
  printf("%s\n", exit_msg);
      free(info->line);
      free(info);
      free_all(info->alloc_head);
  exit(1);
}

void print_arr(char **str) {
  int i;

  i = -1;
  while (str[++i])
    printf("%s\n", str[i]);
}

bool is_space(char c) {
  if (c == ' ' || c == '\t')
    return (TRUE);
  return (FALSE);
}
int quote_len(char *line, t_info *info) {
  int i;
  int j;

  i = info->cursor;
  j = 0;
  if (line[i] && line[i - 1] == 34)
  {
    while (line[i])
    {
      if (line[i] && line[i] == 34)
        return (j);
      i++;
      j++;
    }
  }
  else if (line[i - 1] == 39)
  {
  while (line[i]) {
    if (line[i] && line[i] == 39)
      return (j);
    i++;
    j++;
  }

  }
  return (-1);
}

bool is_operator(char c) {
  if (c == '|' || c == '>' || c == '<')
    return (TRUE);
  return (FALSE);
}

bool is_quote(char c) {
  if (c == DQUOTE || c == QUOTE)
    return (TRUE);
  return (FALSE);
}

int last_char_in_word(char *line, t_info *info) {
  int i;

  i = info->cursor;
  while (line[i] != '\0' && !is_space(line[i]) && !is_quote(line[i]))
    i++;
  i--;
  return (i);
}

int word_len(t_info *info) {
  int i;
  int j;

  i = info->cursor;
  j = 0;
  while (info->line[i] != '\0' && !is_space(info->line[i]) &&
         !is_quote(info->line[i]) && !is_operator(info->line[i])){
    i++;
    j++;
  }
  return (j);
}

//segv here when u start the line with a quote
bool valid_quotes(t_info *info) {
  char *line;
  int i;
  int quote_c;
  int dquote_c;

  line = info->line;
  i = 0;
  quote_c = 0;
  dquote_c = 0;
  while (line[i]) {
    if (line[i] == DQUOTE)
      dquote_c++;
    if (line[i] == QUOTE)
      quote_c++;
    i++;
  }
  if (dquote_c % 2 != 0 && dquote_c != 0) {
    printf("invalid quotes\n");
    return (FALSE);
  }
  if (quote_c % 2 != 0 && quote_c != 0) {
    printf("invalid quotes\n");
    return (FALSE);
  }
  return (TRUE);
}

const char *translate(int c) {
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
  return NULL;
}

void print_tokens(t_oken *head_token) {
  t_oken *ptr = head_token;
  while (ptr->next != NULL) {
    printf("token :%s--quote value =>%d--type =>%s , join_next : %d \n", ptr->token,
           ptr->quote_type, translate(ptr->data_type), ptr->join_next);
    ptr = ptr->next;
  }
    printf("token :%s--quote value =>%d--type =>%s , join_next : %d\n", ptr->token,
           ptr->quote_type, translate(ptr->data_type), ptr->join_next);
}

 char *chad_strdup(const char *s1, t_alloc *alloc_head) {
  size_t len;
  char *dupped_str;
  size_t i;

  len = ft_strlen(s1);
  i = 0;
  dupped_str = (char *)chad_alloc(sizeof(char) , (len + 1), alloc_head);
  if (!dupped_str)
    return (NULL);
  while (s1[i]) {
    dupped_str[i] = s1[i];
    i++;
  }
  dupped_str[i] = '\0';
  return (dupped_str);
}

char	*chad_strjoin(const char *s1, const char *s2, t_alloc *alloc_head)
{
	size_t	i;
	size_t	j;
	size_t	full_len;
	char	*full_str;

	i = 0;
	j = 0;
	full_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	full_str = (char *)chad_alloc(full_len , sizeof(char), alloc_head);
	if (!full_str)
		return (NULL);
	while (s1[i] && i < full_len)
	{
		full_str[i] = s1[i];
		i++;
	}
	while (s2[j] && i < full_len)
		full_str[i++] = s2[j++];
	full_str[i] = '\0';
	return (full_str);
}