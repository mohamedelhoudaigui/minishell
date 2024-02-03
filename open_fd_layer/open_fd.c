/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 05:00:27 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/03 09:06:09 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			fd = here_doc(in_file->file, env_adr, false);
		if (fd == -1)
		{
			perror("open");
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
		if(out_file->type == 2)
			fd = open(out_file->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (out_file->type == 4)
			fd = open(out_file->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
		{
			ft_putstr_fd("open: Permission denied\n", 2);
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

t_commands	*open_fd(t_parsing	*commands, t_list **env_adr)
{
	t_commands	*head;
	t_commands	*temp;
	t_redir		*in;
	t_redir		*out;
	char		**args;

	if (!commands)
		return (NULL);
	head = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (!head)
		return (NULL);
	in = commands->in_fd;
	out = commands->out_fd;
	args = commands->command;
	head->in = handle_in_files(in, env_adr);
	head->out = handle_out_files(out);
	head->command = alloc_commands(args);
	commands = commands->next;
	while (commands)
	{
		temp = (t_commands *)ft_calloc(1, sizeof(t_commands));
		in = commands->in_fd;
		out = commands->out_fd;
		args = commands->command;
		temp->in = handle_in_files(in, env_adr);
		temp->out = handle_out_files(out);
		temp->command = alloc_commands(args);
		command_add_back(&head, temp);
		commands = commands->next;
	}
	free_parse_args(commands);
	return (head);
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
		if (in != 0 && in != 1 && in != 2)
			close(in);
		if (out != 0 && out != 1 && out != 2)
			close(out);
		args = args->next;
	}
}

void	free_parse_args(t_parsing *commands)
{
	char	**args;
	int		i;
	t_redir	*in;
	t_redir	*out;

	if (!commands)
		return ;
	while (commands)
	{
		args = commands->command;
		in = commands->in_fd;
		out = commands->out_fd;
		if (args != NULL)
		{
			i = 0;
			while (args[i])
				free(args[i++]);
			free(args);
		}
		if (in != NULL)
		{
			while (in)
			{
				free(in->file);
				free(in);
				in = in->next;
			}
		}
		if (out != NULL)
		{
			while (out)
			{
				free(out->file);
				free(out);
				out = out->next;
			}
		}
		free(commands);
		commands = commands->next;
	}
}
