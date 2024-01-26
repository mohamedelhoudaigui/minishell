/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:59:04 by mel-houd          #+#    #+#             */
/*   Updated: 2023/11/09 11:03:24 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(const char *s1, const char *s2)
{
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	return (size + 1);
}

static int	check_strings(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (-1);
	if (!s1)
		return (1);
	if (!s2)
		return (2);
	return (0);
}

static char	*malloc_space(size_t size)
{
	char	*res;

	res = (char *)malloc(size * sizeof(char));
	if (!res)
		return (NULL);
	return (res);
}

static char	*concate_strings(char const *s1, char const *s2, char *res)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;

	if (check_strings(s1, s2) == -1)
		return (NULL);
	else if (check_strings(s1, s2) == 1)
		return (ft_strdup(s2));
	else if (check_strings(s1, s2) == 2)
		return (ft_strdup(s1));
	size = get_size(s1, s2);
	res = malloc_space(size);
	if (!res)
		return (NULL);
	res = concate_strings(s1, s2, res);
	return (res);
}
