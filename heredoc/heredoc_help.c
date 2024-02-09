/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:24:03 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/08 20:38:42 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

int	handle_expansion(char **line_d, t_list **env_adr, int file, int i)
{
	char	*expanded_var;
	char	*value;
	int		len;

	value = get_expande_var(&(*line_d)[i]);
	len = ft_strlen(value);
	expanded_var = expande_var(env_adr, value);
	free(value);
	while ((*line_d)[i] && (*line_d)[i + 1] != ' ' && (*line_d)[i + 1] != '\t'
		&& (*line_d)[i + 1] != 34 && (*line_d)[i + 1] != 39)
		i++;
	if (expanded_var != NULL)
	{
		write(file, expanded_var, ft_strlen(expanded_var));
		free(expanded_var);
	}
	return (len - 2);
}

void	check_expansion(char **line_d, t_list **env_adr, int file)
{
	int	i;

	if (!line_d || *line_d == NULL)
		return ;
	i = 0;
	while ((*line_d)[i])
	{
		if ((*line_d)[i] == '$')
			i += handle_expansion(line_d, env_adr, file, i);
		else
			write(file, &(*line_d)[i], 1);
		i++;
	}
	write(file, "\n", 1);
}
