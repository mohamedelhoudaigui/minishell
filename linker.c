/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 01:24:27 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/parse.h"
#include "inc/execution.h"

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

  signal(SIGQUIT, cmd_sig_handel);
  signal(SIGINT, cmd_sig_handel);
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
      printf("exit\n");
      exit(exit_status);
    }
    if (line[0] == '\0' || line_is_empty(line))
    {
      chad_free(info, alloc_head);
      return;
    }
    add_history(line);
    info->line = line;
    info->env = env_adr;
    if (!tokenizer(line, info))
    {
      chad_free(info, alloc_head);
      return;
    }
    join_quotes(info->head, info);
    cmd = lexer(info);
    if(cmd == NULL)
    {
      chad_free(info, alloc_head);
      return;
    }
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
    signal(SIGINT, cmd_sig_loop);
   info = ft_calloc(1, sizeof(t_info));
    alloc_head = ft_calloc(1, sizeof(t_alloc));
    alloc_head->next = NULL;
    alloc_head->address = ft_strdup("placeholder");
    info->alloc_head = alloc_head;
    info->head = NULL;
    chad_readline(info, alloc_head, env_adr);

  }
}