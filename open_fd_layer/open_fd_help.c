/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:44:31 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/05 17:45:01 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"
#include "../inc/parse.h"

char	**alloc_commands(char **com_args)
{
	char	**res;
	int		i;

	if (!com_args)
		return (NULL);
	i = 0;
	while (com_args[i])
		i++;
	res = (char **)ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (com_args[i])
	{
		res[i] = ft_strdup(com_args[i]);
		i++;
	}
	return (res);
}

int	handle_in_files(t_redir	*in_file, t_list **env_adr)
{
	int	fd;

	if (!in_file)
		return (0);
	fd = -1;
	while (in_file)
	{
		if (in_file->type == 1)
			fd = open(in_file->file, O_RDONLY, 0777);
		if (in_file->type == 3)
			fd = here_doc(in_file->file, env_adr, in_file->heredoc_ex);
		if (fd == -1)
		{
			ft_putstr_fd("open: Error opening file\n", 2);
			break ;
		}
		if (in_file->next != NULL)
			close(fd);
		in_file = in_file->next;
	}
	return (fd);
}

int	handle_out_files(t_redir	*out_file)
{
	int	fd;

	if (!out_file)
		return (1);
	fd = -1;
	while (out_file)
	{
		if (out_file->type == 2)
			fd = open(out_file->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (out_file->type == 4)
			fd = open(out_file->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
		{
			ft_putstr_fd("open: Error opening file\n", 2);
			break ;
		}
		if (out_file->next != NULL)
			close(fd);
		out_file = out_file->next;
	}
	return (fd);
}

void	command_add_back(t_commands **head, t_commands *node)
{
	t_commands	*head_d;

	if (!head || !node)
		return ;
	head_d = *head;
	if (head_d == NULL)
	{
		*head = node;
		return ;
	}
	else
	{
		while (head_d->next != NULL)
			head_d = head_d->next;
		head_d->next = node;
	}
}

void	close_all_fd(t_commands *args)
{
	int	in;
	int	out;

	if (!args)
		return ;
	while (args)
	{
		in = args->in;
		out = args->out;
		close(in);
		close(out);
		args = args->next;
	}
}
