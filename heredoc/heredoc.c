/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:29:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/06 23:33:37 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

char	*get_expande_var(char *line)
{
	int		i;
	int		len;
	char	*value;
	char	*tmp;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == 34 || line[i] == 39)
			break ;
		i++;
		len++;
	}
	tmp = ft_substr(line, 0, len);
	value = ft_strjoin(tmp, "=");
	free(tmp);
	return (value);
}

int	open_files(int *file, int *read_file)
{
	*file = open("/tmp/.tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	*read_file = open("/tmp/.tmp", O_RDWR, 0777);
	unlink("/tmp/.tmp");
	if (!*file)
	{
		perror("open");
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

void	handle_read(char **read, t_list **env_adr, int file, bool flag)
{
	if (flag == true)
		check_expansion(read, env_adr, file);
	else
	{
		write(file, *read, ft_strlen(*read));
		write(file, "\n", 1);
	}
	free(*read);
}

int	here_doc(char *delimiter, t_list **env_adr, bool flag)
{
	char		*read;
	int			file;
	int			read_file;

	if (open_files(&file, &read_file) == -1)
		return (-1);
	while (1)
	{
		here_doc_sig();
		read = readline("> ");
		if (read == NULL)
			break ;
		if (ft_strncmp(read, delimiter, ft_strlen(read)
				+ ft_strlen(delimiter)) == 0)
		{
			free(read);
			break ;
		}
		handle_read(&read, env_adr, file, flag);
	}
	close(file);
	return (read_file);
}
