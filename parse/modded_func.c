/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modded_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:23:29 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/02/06 20:25:43 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

char	*chad_strdup(const char *s1, t_alloc *alloc_head)
{
	size_t	len;
	char	*dupped_str;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	dupped_str = (char *)chad_alloc(sizeof(char), (len + 1), alloc_head);
	if (!dupped_str)
		return (NULL);
	while (s1[i])
	{
		dupped_str[i] = s1[i];
		i++;
	}
	dupped_str[i] = '\0';
	return (dupped_str);
}

char	*chad_strjoin(const char *s1, const char *s2, t_alloc *alloc_head)
{
	size_t	i;
	size_t	j;
	size_t	full_len;
	char	*full_str;

	i = 0;
	j = 0;
	full_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	full_str = (char *)chad_alloc(full_len, sizeof(char), alloc_head);
	if (!full_str)
		return (NULL);
	while (s1[i] && i < full_len)
	{
		full_str[i] = s1[i];
		i++;
	}
	while (s2[j] && i < full_len)
		full_str[i++] = s2[j++];
	full_str[i] = '\0';
	return (full_str);
}
