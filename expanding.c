/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:16:51 by mel-houd          #+#    #+#             */
/*   Updated: 2024/01/18 12:38:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_expande(char *dollar_var, t_list *env_var)
{
	int		i;
	int		j;
	int		size;
	char	*content;

	if (env_var == NULL)
	{
		perror("no env vars to expande\n");
		return (1);
	}
	i = 1;
	size = 0;
	while (dollar_var[i] && dollar_var[i] != ' ' && dollar_var[i] != '\t')
	{
		i++;
		size++;
	}
	i = 0;
	while (env_var)
	{
		content = (char *)env_var->content;
		if (ft_strncmp(content, &dollar_var[1], size) == 0)
		{
			j = 0;
			while (content[j] && content[j] != '=')
				j++;
			while (content[++j])
				printf("%c", content[j]);
			return (0);
		}
		env_var = env_var->next;
	}
	return (1);
}
