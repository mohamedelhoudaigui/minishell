
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:11:43 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/07 05:06:48 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/parse.h"
#include "inc/execution.h"

void	chad_free(t_info *info)
{
	free(info->line);
	free_all(info->alloc_head);
	free(info);
}

void	linker(t_info *info, t_list **env_adr)
{
	t_commands	*exec_coms;
	int			o_stdin;
	int			o_stdout;

	o_stdin = dup(0);
	o_stdout = dup(1);
	exec_coms = open_fd(info->cmd, env_adr);
	execution(env_adr, exec_coms);
	close_all_fd(exec_coms);
	ft_clear_commands(&exec_coms);
	reset_fd(o_stdin, o_stdout);
}

void	handle_line(t_info *info, char *line, t_list **env_adr)
{
	t_cmd	*cmd;

	info->line = line;
	if (line[0] == '\0' || line_is_empty(line))
	{
		chad_free(info);
		return ;
	}
	add_history(line);
	if (!tokenizer(line, info))
	{
		chad_free(info);
		return ;
	}
	join_quotes(info->head, info);
	cmd = parser(info);
	if (cmd == NULL)
	{
		chad_free(info);
		return ;
	}
	linker(info, env_adr);
	chad_free(info);
}

void	chad_readline(t_info *info, t_list **env_adr)
{
	char	*line;

	info->cursor = 0;
	info->env = env_adr;
	line = readline("Lbroshell$ ");
	if (!line)
	{
		chad_free(info);
		printf("exit\n");
		exit(g_exit_status);
	}
	handle_line(info, line, env_adr);
}

void	main_loop(t_list **env_adr)
{
	t_info	*info;
	t_alloc	*alloc_head;

	while (TRUE)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		cmd_sig_loop();
		info = ft_calloc(1, sizeof(t_info));
		alloc_head = ft_calloc(1, sizeof(t_alloc));
		alloc_head->next = NULL;
		alloc_head->address = ft_strdup("placeholder");
		info->alloc_head = alloc_head;
		info->head = NULL;
		chad_readline(info, env_adr);
		free(alloc_head);
	}
}
