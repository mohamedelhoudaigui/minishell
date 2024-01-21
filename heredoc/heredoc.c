/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 07:29:37 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/20 14:22:21 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// no expantion , subject said : << should be given a delimiter,
// then read the input until a line containing the
// delimiter is seen. However, it doesn’t have to update the history

// no expande ?? :)

int	here_doc(t_commands *args)
{
	char	*read;
	char	*delimiter;
	int		fd[2];

	delimiter = args->command[1];
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while(1)
	{
		read = readline(">");
		if (ft_strncmp(read, delimiter, ft_strlen(read)) == 0)
		{
			free(read);
			break ;
		}
		write(fd[1], read, ft_strlen(read));
		write(fd[1], "\n", 1);
		free(read);
	}
	close(fd[0]);
	return (fd[1]);
}
