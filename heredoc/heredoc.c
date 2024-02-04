/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:29:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/04 14:22:13 by mel-houd         ###   ########.fr       */
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

void	check_expansion(char **line_d, t_list **env_adr, int file)
{
	char	*line;
	int		i;
	char	*expanded_var;
	char	*value;

	if (!line_d || *line_d == NULL)
		return ;
	i = 0;
	line = *line_d;
	while (line[i])
	{
		if (line[i] == '$')
		{
			value = get_expande_var(&line[i]);
			expanded_var = expande_var(env_adr, value);
			free(value);
			while (line[i] && line[i + 1] != ' ' && line[i + 1] != '\t' && line[i + 1] != 34 && line[i + 1] != 39)
				i++;
			if (expanded_var != NULL)
			{
				write(file, expanded_var, ft_strlen(expanded_var));
				free(expanded_var);
			}
		}
		else
			write(file, &line[i], 1);
		i++;
	}
	write(file, "\n", 1);
}

int	here_doc(char *delimiter ,t_list **env_adr, bool flag)
{
	char	*read;
	int		file;
	int		read_file;

	signal(SIGQUIT, SIG_IGN);
	file = open("/tmp/.tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	read_file = open("/tmp/.tmp", O_RDWR, 0777);
	unlink("/tmp/.tmp");
	if (!file)
	{
		perror("open");
		exit_status = 1;
		return (-1);
	}
	while(1)
	{
		read = readline("> ");
		if (read == NULL)
		{
			write(1, "\n", 1);
			break ;
		}
		if (ft_strncmp(read, delimiter, ft_strlen(read) + ft_strlen(delimiter)) == 0)
		{
			free(read);
			break ;
		}
		if (flag == true)
			check_expansion(&read, env_adr, file);
		else
		{
			write(file, read, ft_strlen(read));
			write(file, "\n", 1);
		}
		free(read);
	}
	close(file);
	return (read_file);
}
