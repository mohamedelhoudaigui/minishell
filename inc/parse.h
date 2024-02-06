

#ifndef PARSE_H
#define PARSE_H

#include "../libft/libft.h"
#include "garbage.h"
#include "macros.h"
#include <limits.h>
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern int exit_status;

typedef struct s_token {
  int data_type;
  char *token;
  struct s_token *next;
  struct s_token *prev;
  bool dollar_presence;
  bool  join_next;
  int quote_type;
} t_oken;

typedef struct s_cmd {
  char **cmd;
  struct s_cmd *next;
  struct s_cmd *prev;
  struct s_redir *redir;
  struct s_redir *redir_out;
} t_cmd;

typedef struct s_redir {
  int type;
  char *file;
  bool heredoc_ex;
  struct s_redir *next;
  } t_redir;

typedef struct s_info {
  t_alloc *alloc_head;
  t_list **env;
  t_cmd *cmd;
  char *line;
  int cursor;
  struct s_token *head;
} t_info;


void	parse_error(const char *exit_msg, t_info *info);
void	print_arr(char **str);
bool	is_space(char c);
int	quote_len(char *line, t_info *info);
bool	is_operator(char c);
bool	is_quote(char c);
int	last_char_in_word(char *line, t_info *info);
void	print_tokens(t_oken *head);
void	handle_operator(char *line, t_info *info);
t_oken *handle_word(char *line, t_info *info);
void	handle_dollar(char *line, t_info *info);
void  main_loop(t_list **env_adr);
bool	check_line(char *line, t_info *info);
int	word_len(t_info *info);
bool	valid_quotes(t_info *info);
bool	is_operator(char c);
t_cmd *lexer(t_info *info);
bool	is_op(int op);
void print_cmd(t_cmd *cmd);
void print_all_cmd(t_cmd *cmd); 
const char *translate(int c);
char	*chad_strjoin(const char *s1, const char *s2, t_alloc *alloc_head);
char *chad_strdup(const char *s1, t_alloc *alloc_head);
void	print_redir(t_redir *redir);
bool	check_token_syntax(t_oken *tokens);
void  chad_free(t_info *info, t_alloc *alloc_head);
bool  line_is_empty(char *line);
t_info *tokenizer(char *line, t_info *info);
void  join_quotes(t_oken *head, t_info *info);

bool	check_dollar_presence(t_oken *tokens);

int		return_dollar_index(char *str);


#endif
